import curses
import subprocess
import threading
import queue
import time
import sys
import os
import textwrap
from datetime import datetime

# ── State ─────────────────────────────────────────────────────────────────────
messages      = []           # list of (user, msg, timestamp) tuples
users         = set()
input_buffer  = ""
username      = ""
message_queue = queue.Queue()
scroll_offset = 0            # 0 = bottom; positive = scrolled up
display_name  = ""
# ── Box-drawing characters (double line) ──────────────────────────────────────
TL, TR, BL, BR = '\u2554', '\u2557', '\u255a', '\u255d'
HZ, VT         = '\u2550', '\u2551'
LT, RT         = '\u2560', '\u2563'   # left-T, right-T

# ── Color pair IDs ────────────────────────────────────────────────────────────
C_OWN    = 1   # own messages           – bright cyan + bold
C_OTHER  = 2   # others' messages       – white
C_SYS    = 3   # system messages        – yellow bold
C_HIST   = 4   # HISTORY messages       – dim white
C_HEADER = 5   # header bar             – black on cyan
C_USER   = 6   # other users in list   – green
C_ME     = 7   # own name in list       – cyan bold
C_DM     = 8   # DM / @mention          – magenta bold
C_INPUT  = 9   # input text             – bright white
C_BORDER = 10  # box borders            – blue dim
C_TITLE  = 11  # panel titles           – yellow bold
C_TIME   = 12  # timestamp brackets     – cyan dim
C_STATUS = 13  # status bar             – black on green

def init_colors():
    curses.start_color()
    curses.use_default_colors()   # -1 = terminal default background
    curses.init_pair(C_OWN,    curses.COLOR_CYAN,    -1)
    curses.init_pair(C_OTHER,  curses.COLOR_WHITE,   -1)
    curses.init_pair(C_SYS,    curses.COLOR_YELLOW,  -1)
    curses.init_pair(C_HIST,   curses.COLOR_WHITE,   -1)
    curses.init_pair(C_HEADER, curses.COLOR_BLACK,   curses.COLOR_CYAN)
    curses.init_pair(C_USER,   curses.COLOR_GREEN,   -1)
    curses.init_pair(C_ME,     curses.COLOR_CYAN,    -1)
    curses.init_pair(C_DM,     curses.COLOR_MAGENTA, -1)
    curses.init_pair(C_INPUT,  curses.COLOR_WHITE,   -1)
    curses.init_pair(C_BORDER, curses.COLOR_BLUE,    -1)
    curses.init_pair(C_TITLE,  curses.COLOR_YELLOW,  -1)
    curses.init_pair(C_TIME,   curses.COLOR_CYAN,    -1)
    curses.init_pair(C_STATUS, curses.COLOR_BLACK,   curses.COLOR_GREEN)

# ── Safe drawing helpers ───────────────────────────────────────────────────────

def safe_addstr(stdscr, y, x, text, attr=0):
    h, w = stdscr.getmaxyx()
    if y < 0 or y >= h or x >= w or x < 0:
        return
    max_len = w - x - 1
    if max_len <= 0:
        return
    try:
        stdscr.addstr(y, x, text[:max_len], attr)
    except curses.error:
        pass

def safe_addch(stdscr, y, x, ch, attr=0):
    h, w = stdscr.getmaxyx()
    if 0 <= y < h and 0 <= x < w:
        try:
            stdscr.addch(y, x, ch, attr)
        except curses.error:
            pass

def draw_hline(stdscr, y, x, ch, n, attr=0):
    for i in range(n):
        safe_addch(stdscr, y, x + i, ch, attr)

def draw_vline(stdscr, y, x, ch, n, attr=0):
    for i in range(n):
        safe_addch(stdscr, y + i, x, ch, attr)

def draw_box(stdscr, y, x, h, w, attr=0):
    """Draw a double-line box at (y, x) with size (h, w)."""
    if h < 2 or w < 2:
        return
    safe_addch(stdscr, y,       x,       TL, attr)
    safe_addch(stdscr, y,       x+w-1,   TR, attr)
    safe_addch(stdscr, y+h-1,   x,       BL, attr)
    safe_addch(stdscr, y+h-1,   x+w-1,   BR, attr)
    draw_hline(stdscr, y,       x+1,     HZ, w-2, attr)
    draw_hline(stdscr, y+h-1,   x+1,     HZ, w-2, attr)
    draw_vline(stdscr, y+1,     x,       VT, h-2, attr)
    draw_vline(stdscr, y+1,     x+w-1,   VT, h-2, attr)

def now_str():
    return datetime.now().strftime("%H:%M")

# ── Message attribute resolver ────────────────────────────────────────────────

def get_msg_attr(user, msg):
    if user == username:
        return curses.color_pair(C_OWN) | curses.A_BOLD
    if user == "SYSTEM":
        return curses.color_pair(C_SYS) | curses.A_BOLD
    if user == "HISTORY":
        return curses.color_pair(C_HIST) | curses.A_DIM
    # Highlight @mention DMs
    if f"@{username}" in msg:
        return curses.color_pair(C_DM) | curses.A_BOLD
    return curses.color_pair(C_OTHER)

# ── Background reader thread ──────────────────────────────────────────────────

def read_from_client(proc):
    """Read client output in a background thread and push into the queue."""
    try:
        while True:
            line = proc.stdout.readline()
            if not line:
                continue

            line = line.strip()

            if not line:
                continue

            if line.lower().strip() == "enter username:":
                continue

            if ":" in line and not line.startswith(">"):
                parts = line.split(":", 1)
                if len(parts) < 2:
                    message_queue.put(("SYSTEM", line))
                    continue
                user = parts[0].strip()
                msg  = parts[1].strip()
                message_queue.put((user, msg))
            else:
                message_queue.put(("SYSTEM", line))
    except Exception:
        pass

# ── Welcome / username screen ─────────────────────────────────────────────────

def username_screen(stdscr):
    """Draw a centered login box and return the entered username."""
    stdscr.clear()
    h, w = stdscr.getmaxyx()
    border_attr = curses.color_pair(C_BORDER) | curses.A_DIM
    title_attr  = curses.color_pair(C_TITLE)  | curses.A_BOLD

    box_h, box_w = 9, 52
    by = max(0, (h - box_h) // 2)
    bx = max(0, (w - box_w) // 2)

    draw_box(stdscr, by, bx, box_h, box_w, border_attr)

    title = "[ IPC CHAT ]"
    safe_addstr(stdscr, by, bx + (box_w - len(title)) // 2, title, title_attr)

    safe_addstr(stdscr, by + 2, bx + 3,
                "Welcome! Please enter your username below.",
                curses.color_pair(C_OTHER))
    safe_addstr(stdscr, by + 4, bx + 3,
                "Username : ",
                curses.color_pair(C_INPUT) | curses.A_BOLD)
    safe_addstr(stdscr, by + 6, bx + 3,
                "Press Enter to join the chat.",
                curses.A_DIM)

    stdscr.refresh()
    curses.echo()
    curses.curs_set(1)
    try:
        stdscr.move(by + 4, bx + 14)
        stdscr.refresh()
        raw = stdscr.getstr(by + 4, bx + 14, 25)
        name = raw.decode('utf-8').strip()
        stdscr.refresh()
    except Exception:
        name = ""
    curses.noecho()
    return name or f"username_{os.getpid()}"

# ── Main draw function ────────────────────────────────────────────────────────

def draw_ui(stdscr):
    global scroll_offset

    stdscr.erase()
    h, w = stdscr.getmaxyx()

    if h < 14 or w < 52:
        safe_addstr(stdscr, 0, 0, "Terminal too small – please resize!", curses.A_BOLD)
        stdscr.refresh()
        return

    border_attr = curses.color_pair(C_BORDER) | curses.A_DIM
    title_attr  = curses.color_pair(C_TITLE)  | curses.A_BOLD
    header_attr = curses.color_pair(C_HEADER) | curses.A_BOLD
    status_attr = curses.color_pair(C_STATUS) | curses.A_BOLD

    panel_w = max(16, min(int(w * 0.22), 26))

    # ── Header bar (row 0) ───────────────────────────────────────────────────
    header = f" [IPC CHAT]  User: {display_name}  |  ^/v scroll  |  Ctrl+C exit "
    safe_addstr(stdscr, 0, 0, " " * (w - 1), header_attr)
    safe_addstr(stdscr, 0, 0, header, header_attr)

    # ── Panel boxes (rows 1 .. h-5) ──────────────────────────────────────────
    main_h = h - 5   # height for left + right panels
    draw_box(stdscr, 1, 0,        main_h, panel_w,      border_attr)  # left
    draw_box(stdscr, 1, panel_w,  main_h, w - panel_w,  border_attr)  # right

    # Panel titles embedded in border
    safe_addstr(stdscr, 1, 2,           " Online ", title_attr)
    safe_addstr(stdscr, 1, panel_w + 2, " Messages ", title_attr)

    online_count = f"({len(users)})"
    safe_addstr(stdscr, 1, 10, online_count, curses.color_pair(C_SYS) | curses.A_BOLD)

    msg_count = f"[{len(messages)}]"
    safe_addstr(stdscr, 1, panel_w + 12, msg_count, curses.color_pair(C_SYS))

    # ── Users list ───────────────────────────────────────────────────────────
    max_users = main_h - 3
    sorted_users = sorted(list(users))
    uy = 3
    for u in sorted_users[:max_users]:
        if uy >= 1 + main_h - 1:
            break

        label = u.split("_")[0]   # show clean name

        if u == username:
            safe_addstr(stdscr, uy, 1, "> " + label[:panel_w - 4],
                        curses.color_pair(C_ME) | curses.A_BOLD)
        else:
            safe_addstr(stdscr, uy, 1, "  " + label[:panel_w - 4],
                        curses.color_pair(C_USER))

        uy += 1

    if not users:
        safe_addstr(stdscr, 3, 2, "(no users)", curses.A_DIM)

    # ── Build wrapped message lines ──────────────────────────────────────────
    chat_x = panel_w + 2
    chat_w = w - panel_w - 4
    chat_h = main_h - 3   # lines available for messages inside box

    wrapped = []   # list of (attr, text)
    for user, msg, ts in messages:
        attr = get_msg_attr(user, msg)
        if user == username:
            prefix = f"[{ts}] You: "
        elif user in ("SYSTEM", "HISTORY"):
            prefix = f"[{ts}] # "
        else:
            prefix = f"[{ts}] {user}: "

        avail = max(10, chat_w - len(prefix))
        chunks = textwrap.wrap(msg, avail) or [""]
        for i, chunk in enumerate(chunks):
            if i == 0:
                wrapped.append((attr, prefix + chunk))
            else:
                wrapped.append((attr, " " * len(prefix) + chunk))

    # Clamp scroll offset
    total = len(wrapped)
    scroll_offset = min(scroll_offset, max(0, total - chat_h))
    start   = max(0, total - chat_h - scroll_offset)
    visible = wrapped[start: start + chat_h]

    cy = 3
    for attr, line in visible:
        if "You:" in line:
            # RIGHT ALIGN (fixed safe positioning)
            x_pos = chat_x + max(0, chat_w - len(line))
            safe_addstr(stdscr, cy, x_pos, line, attr)
        else:
            # LEFT ALIGN
            safe_addstr(stdscr, cy, chat_x, line, attr)
        cy += 1

    # Scroll indicator
    if scroll_offset > 0:
        ind = f" ^ scrolled {scroll_offset} lines  (DOWN to resume) "
        safe_addstr(stdscr, 1 + main_h - 2, panel_w + 2, ind,
                    curses.color_pair(C_DM) | curses.A_BOLD)

    # ── Input box (rows h-4 .. h-2) ──────────────────────────────────────────
    input_y = h - 4
    draw_box(stdscr, input_y, 0, 3, w, border_attr)

    label = " MSG "
    safe_addstr(stdscr, input_y, 2, label, title_attr)
    hint = "Enter=send  @user=DM  Ctrl+C=quit"
    safe_addstr(stdscr, input_y, 2 + len(label), hint,
                curses.color_pair(C_SYS) | curses.A_DIM)

    char_cnt = str(len(input_buffer))
    safe_addstr(stdscr, input_y, w - len(char_cnt) - 3, char_cnt, curses.A_DIM)

    prompt       = "> "
    display_inp  = (prompt + input_buffer)[: w - 4]
    safe_addstr(stdscr, input_y + 1, 2, display_inp,
                curses.color_pair(C_INPUT) | curses.A_BOLD)

    # ── Status bar (last row) ─────────────────────────────────────────────────
    status = f" [CONNECTED]  {len(messages)} messages  |  {len(users)} online "
    safe_addstr(stdscr, h - 1, 0, " " * (w - 1), status_attr)
    safe_addstr(stdscr, h - 1, 0, status, status_attr)

    # Cursor to end of input
    cursor_x = min(2 + len(prompt) + len(input_buffer), w - 2)
    try:
        stdscr.move(input_y + 1, cursor_x)
    except curses.error:
        pass

    stdscr.refresh()

# ── Main loop ─────────────────────────────────────────────────────────────────

def main(stdscr):
    global input_buffer, username, scroll_offset, display_name

    curses.curs_set(1)
    init_colors()
    stdscr.timeout(100)
    stdscr.keypad(True)

    stdscr.nodelay(False)                 # allow blocking input
    base_name = username_screen(stdscr)
    stdscr.nodelay(True)
    display_name = base_name
    username = base_name                  # clean username (no _pid)

    # Launch client subprocess
    proc = subprocess.Popen(
        ["./client"],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True,
        bufsize=1,
        universal_newlines=True,
    )

    try:
        proc.stdin.write(username + "\n")
        proc.stdin.flush()
    except Exception:
        safe_addstr(stdscr, 5, 5, "Failed to start client!", curses.A_BOLD)
        stdscr.refresh()
        time.sleep(2)
        return

    users.add(username)
    threading.Thread(target=read_from_client, args=(proc,), daemon=True).start()

    try:
        while True:
            # Drain the incoming-message queue
            while not message_queue.empty():
                try:
                    user, msg = message_queue.get_nowait()
                    messages.append((user, msg, now_str()))

                    if user not in ("SYSTEM", "HISTORY"):
                        users.add(user)
                    elif user == "SYSTEM":
                        msg_lower = msg.lower()
                        if "left chat" in msg_lower:
                            try:
                                left_user = msg.split(" left chat", 1)[0].strip()
                                users.discard(left_user)
                            except:
                                pass
                        elif "joined the chat" in msg_lower:
                            try:
                                join_user = msg.split(" joined the chat", 1)[0].strip()
                                users.add(join_user)
                            except:
                                pass

                except queue.Empty:
                    break

            draw_ui(stdscr)

            ch = stdscr.getch()
            if ch == -1:
                continue

            if ch in (10, 13):            # Enter – send message
                if input_buffer.strip():
                    try:
                        proc.stdin.write(input_buffer + "\n")
                        proc.stdin.flush()
                        # Do NOT add own message here – it will come back via client output
                    except BrokenPipeError:
                        break
                    input_buffer  = ""
                    scroll_offset = 0     # jump to bottom after sending

            elif ch in (127, curses.KEY_BACKSPACE):
                input_buffer = input_buffer[:-1]

            elif ch == 3:                 # Ctrl+C
                break

            elif ch == curses.KEY_UP:
                scroll_offset += 1

            elif ch == curses.KEY_DOWN:
                scroll_offset = max(0, scroll_offset - 1)

            elif ch == curses.KEY_PPAGE:  # Page Up
                scroll_offset += 10

            elif ch == curses.KEY_NPAGE:  # Page Down
                scroll_offset = max(0, scroll_offset - 10)

            elif 32 <= ch <= 126:         # printable ASCII
                input_buffer += chr(ch)

    except KeyboardInterrupt:
        pass
    finally:
        try:
            proc.terminate()
            proc.wait(timeout=2)
        except Exception:
            pass
        curses.endwin()
        print("\nChat closed. Goodbye!")


if __name__ == "__main__":
    try:
        curses.wrapper(main)
    except Exception as e:
        curses.endwin()
        print(f"Error: {e}")
        sys.exit(1)

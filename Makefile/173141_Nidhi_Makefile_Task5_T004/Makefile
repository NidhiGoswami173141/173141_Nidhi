prj1 = Project1
prj2 = Project2

build:
	cd $(prj1) && $(MAKE) && cd ..
	cd $(prj2) && $(MAKE) && cd ..

execute:
	./Project1/Project1.out
	./Project2/Project2.out

clean:
	rm -f Project1/*.o Project1/Project1.out
	rm -f Project2/*.o Project2/Project2.out 

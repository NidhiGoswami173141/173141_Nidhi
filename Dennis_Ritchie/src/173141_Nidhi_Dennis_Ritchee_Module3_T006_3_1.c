/*
Author: Nidhi Goswami
Date : 24-02-2026
Description : Our binary search makes two tests inside the loop, when one would suffice (at the price of more tests outside.) Write a version with only one test inside the loop and measure the difference in run-time
*/


#include<stdio.h>
#include<stdint.h>
#include"module.h"

void binary_search(){

     int32_t number;
     int8_t index;
     int8_t element;

     printf("enter number of element:");
     scanf("%d",&number);
     int32_t arr[number];

     printf("enter array element:\n");
     for( index=0; index<number ; index++){
         scanf("%d",&arr[index]);
     }
     printf("Array:");
     for(index=0 ;index<number ; index++){
         printf("%d ",arr[index]);
     }

     int8_t sorted =1;
     for(index = 0;index<number-1;index++){

        if(arr[index]>arr[index+1]){
           sorted =0;
           break;
        }
     }
     if(sorted == 1){
       printf("\nsorted array\n");
     }
     else{
       printf("\narray is not sorted\n");
       sorting_fun(arr,number);
       printf("Sorted Array: ");
       for(index = 0; index < number; index++){
       printf("%d ", arr[index]);
   }
     }
     int32_t left = 0;
     int32_t right = number - 1;
     int32_t mid;
     int32_t found = 0;

     printf("\nEnter element to search: ");
     scanf("%d", &element);

     while(left < right){
         mid = (left + right) / 2;

         if(element <= arr[mid])
             right = mid;
         else
             left = mid + 1;
     }

     if(arr[left] == element){
         found = 1;
         printf("Element found at index %d\n", left);
     }
     else{
         printf("Element not found\n");
     }
}

void sorting_fun(int32_t arr[], int32_t number){
    int32_t index=0;
    int32_t sec_index;


   for(index=0;index<number-1;index++){
      for(sec_index=0;sec_index<number-index-1;sec_index++){
         if(arr[sec_index]>arr[sec_index+1]){
            int8_t temp = arr[sec_index];
            arr[sec_index]=arr[sec_index+1];
            arr[sec_index+1]=temp;
         }
      }
   }

}



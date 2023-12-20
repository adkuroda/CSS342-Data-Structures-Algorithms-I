
#include <vector>
using namespace std;
/**********************************************************/

/** Bubble Sort: Used course book to implement this*/
void BubbleSort(vector<int>& vec, int start, int end){
    int pass = start + 1;
    int pass1 = 1;
    bool sort_status = false;
    while (pass <= end && !sort_status){
        sort_status = true;
        int index = start;
        while (index <= end - pass1){
            if (vec[index] > vec[index + 1]){
                int temp = vec[index];
                vec[index] = vec[index + 1];
                vec[index + 1] = temp;
                sort_status = false;
            }
            index++;
        }
        pass++;
        pass1++;
    }
}

/**********************************************************/

/** Insertion sort: Used class notes to implement this*/
void InsertionSort(vector<int>& vec, int start, int end){
    for(int place = start +1; place <= end; place ++){
        int temp = vec[place];
        int i = place;
        while ((i > start) && (vec[i -1]) > temp){
            vec[i] = vec[i -1];
            i--;
        }
        vec[i] = temp;
    }
}

/**********************************************************/

/** MergeSort and Merge Algorithm. Used class notes to implment this*/
void Merge(vector<int>& vec, int lhs_st, int lhs_end, 
            int rhs_st, int rhs_end){
    int size = rhs_end - lhs_st + 1;
    int* tmp_arr;
    tmp_arr = new int[size];
    int start = lhs_st;
    int index = 0;
    while ((lhs_st <= lhs_end) && (rhs_st <= rhs_end)){
        if (vec[lhs_st] < vec[rhs_st]){
            tmp_arr[index++] = vec[lhs_st++];
        }else{
            tmp_arr[index++] = vec[rhs_st++];
        }
    }
    while (lhs_st <= lhs_end){
        tmp_arr[index++] = vec[lhs_st++];
    }
    while (rhs_st <= rhs_end){
        tmp_arr[index++] = vec[rhs_st++];
    }
    for (index = 0; index < size; index++)
    {
        vec[start++] = tmp_arr[index];
    }
    delete[] tmp_arr;
}

void MergeSort(vector<int>& vec, int start, int end){
    if (start < end){
        int mid = (start + end)/2;
        MergeSort(vec, start, mid);
        MergeSort(vec, mid+1, end);
        Merge(vec, start, mid,mid +1, end);
    }
}

/**********************************************************/
/** This is similar to Merge Sort Merge algorithm. Instead of 
 * creating new array each time, this function takes pointer to 
 * an integer array to merge elements.
*/
void IterativeMerge(vector<int>& vec, int *temp, int lhs_st,
                    int lhs_end, int rhs_st, int rhs_end){
    int start = lhs_st;
    int index = lhs_st;
    while ((lhs_st <= lhs_end) && (rhs_st <= rhs_end)){
        if (vec[lhs_st] < vec[rhs_st]){
            temp[index++] = vec[lhs_st++];
        }else{
            temp[index++] = vec[rhs_st++];
        }
    }
    while (lhs_st <= lhs_end){
        temp[index++] = vec[lhs_st++];
    }
    while (rhs_st <= rhs_end){
        temp[index++] = vec[rhs_st ++];
    }
    for(int i = start; i <= rhs_end; i ++){
        vec[i] = temp[i];
    }
}
/**
 * This Merge Sort iterates instead of utilizing recursion. I mimics what 
 * will be performed with recursion by merging one element, then two and four 
 * and so on. Outer loop determines initial middle spot where the left and right of 
 * the of mid spot will be merged. Inner loop move the middle spot ensuring 
 * whole vector is splitted and merged accordingly.  
*/
void IterativeMergeSort(vector<int>& vec, int start, int end){
    int * temp = new int[vec.size()];
    int mid = 1; // inital middle spot 
    while (mid <= end){
        for(int i = start; i <= end; i = i + 2*mid){
            int lhs_end = i+ mid -1; // left sided
            int rhs_st = i+ mid; // right side start 
            int rhs_end = 2*mid +i -1; // right side end
             // There is no point of merging: It will not have any effect on the vector
            if (lhs_end >= end){
                break;
            }  
            // There is no point of merging: It will not have any effect on the vector 
            if (rhs_st > end){
                break;
            }
            // This ensures it does not go out of bound
            if(rhs_end > end){
                rhs_end = end;
            }
            IterativeMerge(vec, temp, i, lhs_end, rhs_st, rhs_end);
        }
        mid *= 2; 
    }
    delete[] temp;
}
/**********************************************************/

/*QuickSort: SortFirstMiddleLast, Partition and QuickSort are used to implement
 Quick Sort. I used pseudo code provided in the Carrano book to implement this. */

/** Sorts fist, middle and last elements of a vector and puts in in right order */
void SortFirstMiddleLast(vector<int>& vec, int first, int mid, int last){
    if (vec[first] > vec[last]){
        swap(vec[first], vec[last]);
    }
    if (vec[first] > vec[mid]){
        swap(vec[first], vec[mid]);
    }
    else if (vec[mid] > vec[last]){
        swap(vec[mid], vec[last]);
    }
}
/**********************************************************/
/**This function dividing array into two partition based on pivot. Pivot is selected
 by choosing  middle element in terms of value from 3 elements (start, mid and end)
 in given array*/
int Partition(vector<int>& vec, int start, int end){
    int mid = (start + end)/2;
    SortFirstMiddleLast(vec, start, mid, end);
    int temp = vec[mid];
    vec[mid] = vec[end -1];
    vec[end -1] = temp;
    int pivot = end - 1;
    int pivot_val = vec[pivot];
    bool status = false;
    int left_index = start + 1;
    int right_index = end -2;
    while (!status){
        while(vec[left_index] < pivot_val){
            left_index++;
        }
        while(vec[right_index] > pivot_val){
            right_index--;
        }
        if (left_index < right_index){
            int temp = vec[left_index];
            vec[left_index] = vec[right_index];
            vec[right_index] = temp;
            left_index++;
            right_index--;
        }else{
            status = true;
        }
    }
    vec[pivot] = vec[left_index];
    vec[left_index] = pivot_val;
    pivot = left_index;
    return pivot;
}
/** This is  QuickSort driver, recursively */
void QuickSort(vector<int>& vec, int start, int end){
    if((end - start) < 4){
        InsertionSort(vec, start, end);
    }else{
        int pivot = Partition(vec, start, end);
        QuickSort(vec, start, pivot -1);
        QuickSort(vec, pivot + 1, end);
    }
}

/** Shell sort. Used code provided in class*/

void ShellSort(vector<int>& vec, int start, int end){
    int size = end - start + 1;
    int gap = size/2;
    while (gap > 0){
    for (int i = gap; i < size; i++){
        int tmp = vec[i + start];
        int j = i + start;
        for ( ;(j >= gap + start) && (tmp < vec[j - gap]); j -= gap){
            vec[j] = vec[j - gap];
        }
        vec[j] = tmp;
        }
        if (gap == 2){
            gap = 1;
        }else{
            gap = gap/2.2;
        }
    }
}

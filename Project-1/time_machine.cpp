

#include <iostream>
#include <string>
#include "time_span.h"
// cmath included testing puposes only. Actual code does not include it. 
#include <cmath> 

// testing purose
string status(bool status){
    if (status){
        return "true";
    }else{
        return "false";
    }
}
// testing purose
double total(const TimeSpan& time){
    double ret = time.hours() * 3600 + time.minutes()*60 + time.seconds();
    return ret;
}


int main(int argc, const char * argv[]) {
    //cout << "Hello WOrld" << endl;
    const int kArraySize = 20;
    TimeSpan arr[kArraySize];
    TimeSpan arr1[kArraySize];
    TimeSpan arr2[kArraySize];
    int sec[kArraySize];
    double dsec[kArraySize];
//    double dsec1[kArraySize];
//    double dsec2[kArraySize];
    TimeSpan d1(77.4, 15, 6), d2(127.86), d3(8, -23, 0), d4(0, 0, 0);
    
    TimeSpan dur1(77.4, 15, 6), dur2(127.86), dur3(8, -23, 0), dur4(0, 0, 0);
    TimeSpan dur5(-3, 73, 2), dur6(7, 35, 120), dur7, dur8;
//    dur4.set_time(1, 2, 3);
//    cout << dur5<< endl;
//    dur4 = -dur5;
//    cout << dur4 << endl;
//    cout << dur2 << endl;
    //cout << dur4 << endl;
// Testing format matches
//Hours: 1, Minutes: 2, Seconds: 3
//Hours: 1, Minutes: 2, Seconds: 3
//    
    dur7 = dur1 + dur3;
    cout << dur1 << endl;
   cout << dur2 << endl;
   cout << dur3 << endl;
   cout << dur4 << endl;
   cout << dur5 << endl;
   cout << dur6 << endl;
   cout << dur7 << endl;
    dur7 += dur3;
    cout << dur3 << endl;
   cout << dur7 << endl;
    if (dur3 != dur6)
    {
        cout << "Durations are different." << endl;
    }
     else
     {
         cout << "Durations are the same" << endl;
     }
    
    
//        TimeSpan test1(-100, 60, 60);
//        cout << test1 << endl;
    //    TimeSpan test2(0.50000000000000000000001);
    //    cout << test2 << endl;
    //    TimeSpan test3(-0.999999999999);
    //    cout << test3 << endl;
    //    TimeSpan test4(0.9999999999999);
    //    cout << test4 << endl;
   
//    TimeSpan test5(3659);
//    cout << test5 << endl;
//    TimeSpan test6(59,60);
//    cout << test6 << endl;
    for (int i = 0; i < kArraySize; i++){
        arr[i] = TimeSpan(i*i, i * i, i * i);
        sec[i] = i*i * 3600 + i * i* 60 + i * i;
    }
    for (int i = 0; i < kArraySize; i++){
        cout << arr[i] << endl;
        int hour = sec[i]/3600;
        int min = (sec[i] - hour * 3600)/60;
        int second =sec[i] - hour * 3600 - min *60;
        cout << "Hour   "<< hour << " min      " << min << " sec     " << second<< endl;
        cout << endl;
    }

    for (int i = 0; i < kArraySize; i++){
        if (i == 0){
            cout << -i*i << -i * i << -i * i << endl;
        }
        arr[i] = TimeSpan(-(i*i), -(i * i), -(i * i));
        sec[i] = -(i*i * 3600 + i * i* 60 + i * i);
    }
    for (int i = 0; i < kArraySize; i++){
        cout<< arr[i] << endl;
       int hour = sec[i]/3600;
       int min = (sec[i] -hour * 3600)/60;
       int second =sec[i] - hour * 3600 - min *60;
       cout << "Hours: "<< hour << ", Minutes: " << min << ", Seconds: " << second<< endl;
        cout << endl;
    }
        for (int i = 0; i < kArraySize; i++){
            arr[i] = TimeSpan((i*i), -(i * i), -(i * i));
            sec[i] = (i*i * 3600) -( i * i* 60 +(i * i));
        }
        for (int i = 0; i < kArraySize; i++){
            cout<< arr[i] << endl;
           int hour = sec[i]/3600;
           int min = (sec[i] -hour * 3600)/60;
           int second =sec[i] - hour * 3600 - min *60;
           cout << "Hours: "<< hour << ", Minutes: " << min << ", Seconds: " << second<< endl;
            cout << endl;
        }

  

//        for (int i = 0; i < kArraySize; i++){
//            arr[i] = TimeSpan(-(i*i), (i * i), (i * i));
//            sec[i] = -(i*i * 3600) + ( i * i* 60 +(i * i));
//        }
//        for (int i = 0; i < kArraySize; i++){
//            cout<< arr[i] << endl;
//           int hour = sec[i]/3600;
//           int min = (sec[i] -hour * 3600)/60;
//           int second =sec[i] - hour * 3600 - min *60;
//           cout << "Hours: "<< hour << ", Minutes: " << min << ", Seconds: " << second<< endl;
//            cout << endl;
//        }
    cout << " *******************Decimals *************" << endl;
    cout << endl;
            for (int i = 0; i < kArraySize; i++){
                arr[i] = TimeSpan(-(i*100.3330000000003123456789),
                                  ((i * i)*1.5000000000124),
                                  (i * i)*1.5000000000124);
                dsec[i] = (-(i * 3600)*100.3330000000003123456789) + ( i * i* 60 +(i * i))*1.5000000000124;
            }
//         for (int i = 0; i < kArraySize; i++){
//                arr[i] = TimeSpan((i*i)*0.3330000000003123456789, -(i * i)*0.5000000000124, (i * i)*0.5000000000124);
//                dsec[i] = (i*i * 3600)*0.3330000000003123456789 + ( -(i * i* 60) +(i * i))*0.5000000000124;
//           }
            for (int i = 0; i < kArraySize; i++){
                cout<< arr[i] << endl;
               int hour = dsec[i]/3600;
               int min = (dsec[i] -hour * 3600)/60;
                int second = static_cast<int>(round(dsec[i] - hour * 3600 - min *60));
               cout << "Hours: "<< hour << ", Minutes: " << min << ", Seconds: " << second<< endl;
                cout << endl;
            }
    for (int i = 0; i < kArraySize; i++){
                arr[i] = TimeSpan((i*i)*0.3330000000003123456789, -(i * i)*0.5000000000124, (i * i)*0.5000000000124);
                dsec[i] = (i*i * 3600)*0.3330000000003123456789 + ( -(i * i* 60) +(i * i))*0.5000000000124;
           }
    for (int i = 0; i < kArraySize; i++){
        cout<< arr[i] << endl;
       int hour = dsec[i]/3600;
       int min = (dsec[i] -hour * 3600)/60;
        int second = static_cast<int>(round(dsec[i] - hour * 3600 - min *60));
       cout << "Hours: "<< hour << ", Minutes: " << min << ", Seconds: " << second<< endl;
        cout << endl;
    }
//
//////
    cout << "************Getters and Setters***********" << endl;
    for (int i = 0; i < 10; i++){
                arr[i] = TimeSpan((-i*i), -(i * i), (i * i));
                dsec[i] = -(i*i * 3600) + ( -(i * i* 60) +(i * i));
           }
    for (int i = 10; i < kArraySize; i++){
                arr[i] = TimeSpan((i*i)*10.133, -(i * i)*0.5000000000124, (i * i)*0.5000000000124);
                dsec[i] = (i*i * 3600)*10.133 + ( -(i * i* 60) +(i * i))*0.5000000000124;
           }
    for (int i = 0; i < kArraySize; i++){
        //cout<< arr[i] << endl;
       int hour = dsec[i]/3600;
       int min = (dsec[i] -hour * 3600)/60;
        int second = static_cast<int>(round(dsec[i] - hour * 3600 - min *60));
      cout << "Hours: "<< arr[i].hours()  << ", Minutes: " << arr[i].minutes() << ", Seconds: "
            << arr[i].seconds()<< endl;
       cout << "Hours: "<< hour << ", Minutes: " << min << ", Seconds: " << second<< endl;
        cout << endl;
    }
    cout << "*************** Setters ************" << endl;
    for (int i = 0; i < kArraySize; i++){
        cout<< arr[i] << endl;
       int hour = dsec[i]/3600;
       int min = (dsec[i] -hour * 3600)/60;
        int second = static_cast<int>(round(dsec[i] - hour * 3600 - min *60));
        arr1[i].set_time(hour, min, second);
        cout << arr1[i] << endl;
        cout << endl;
    }
    
   cout << "************Uniary Negation ***********" << endl;
    d1.set_time(1, 1, 1);
    TimeSpan d5 = -d1;
    cout << d1 << endl;
    cout << d5<< endl;
    d5 = -d5;
    cout << d5<< endl;
  cout << "D3" << d3<< endl;
        d4 = -d3;

    cout << d4<< endl;
    d4 = -d4;
    cout << d4<< endl;
    cout << endl;
    

   cout << "************Operator over: += & + ***********" << endl;


    for (int i = 0; i < kArraySize; i++){
        arr[i] = TimeSpan(-(i*i)*1000.3330000000003123456789, (i * i)*10000.5000000000124, (i * i)*10000.5000000000124);
        dsec[i] = -(i*i * 3600)*1000.3330000000003123456789 + ( i * i* 60 +(i * i))*10000.5000000000124;
    }
 for (int i = 0; i < kArraySize; i++){
        arr[i] = TimeSpan((i*i)*0.3330000000003123456789, -(i * i)*0.5000000000124, (i * i)*0.5000000000124);
        dsec[i] = (i*i * 3600)*0.3330000000003123456789 + ( -(i * i* 60) +(i * i))*0.5000000000124;
    }
 for (int i = 0; i < kArraySize; i++){
     TimeSpan t1(i,i, i);
     double a = total(t1);
     double b = total(arr[i]);
     arr[i] += t1;
     cout << TimeSpan(b + a) << endl;
     cout<< arr[i] << endl;
     cout << endl;
 }
    
    cout <<"*************    +=        *************" << endl;
    for (int i = 0; i < kArraySize; i++){
        arr[i] = TimeSpan(-(i*i)*1000.3330000000003123456789, (i * i)*10000.5000000000124, (i * i)*10000.5000000000124);
        dsec[i] = -(i*i * 3600)*1000.3330000000003123456789 + ( i * i* 60 +(i * i))*10000.5000000000124;
    }

 for (int i = 0; i < kArraySize; i++){
     TimeSpan t1(i,i, i);
     double a = total(t1);
     double b = total(arr[i]);
     arr[i] += t1;
     cout << TimeSpan(b + a) << endl;
     cout<< arr[i] << endl;
     cout << endl;
 }
    cout <<"***************    +      ***********" << endl;
        for (int i = 0; i < kArraySize; i++){
            arr[i] = TimeSpan(-(i*i)*1000.3330000000003123456789, (i * i)*10000.5000000000124, (i * i)*10000.5000000000124);
            dsec[i] = -(i*i * 3600)*1000.3330000000003123456789 + ( i * i* 60 +(i * i))*10000.5000000000124;
        }

     for (int i = 0; i < kArraySize; i++){
         TimeSpan t1(i,i, i);
         double a = total(t1);
         double b = total(arr[i]);
         arr[i] = t1 + arr[i];
         cout << TimeSpan(b + a) << endl;
         cout<< arr[i] << endl;
         cout << endl;
     }

    cout << endl;
    
    cout << "************Operator over: -= & - ***********" << endl;
    


            for (int i = 0; i < kArraySize; i++){
                arr[i] = TimeSpan(-(i*i)*1000.3330000000003123456789, (i * i)*10000.5000000000124, (i * i)*10000.5000000000124);
                dsec[i] = -(i*i * 3600)*1000.3330000000003123456789 + ( i * i* 60 +(i * i))*10000.5000000000124;
            }
         for (int i = 0; i < kArraySize; i++){
             TimeSpan t1(i,i, i);
             double a = total(t1);
             double b = total(arr[i]);
             arr[i] -= t1;
             cout << TimeSpan(b -a) << endl;
             cout<< arr[i] << endl;
             cout << endl;
         }
    cout <<"***************    -      ***********" << endl;
    for (int i = 0; i < kArraySize; i++){
        arr[i] = TimeSpan(-(i*i)*1000.3330000000003123456789, (i * i)*10000.5000000000124, (i * i)*10000.5000000000124);
        dsec[i] = -(i*i * 3600)*1000.3330000000003123456789 + ( i * i* 60 +(i * i))*10000.5000000000124;
    }

 for (int i = 0; i < kArraySize; i++){
     TimeSpan t1(i,i, i);
     double a = total(t1);
     double b = total(arr[i]);
     arr[i] = t1 - arr[i];
     cout << TimeSpan(a - b) << endl;
     cout<< arr[i] << endl;
     cout << endl;
 }


 for (int i = 0; i < kArraySize; i++){
     TimeSpan t1(i * 0.00001,i, i);
     double a = total(t1);
     double b = total(arr[i]);
     arr[i] =  arr[i] -t1;
     cout << TimeSpan(b -a) << endl;
     cout<< arr[i] << endl;
     cout << endl;
 }

    cout << " ******THis one should double *****" << endl;

    for (int i = 0; i < kArraySize; i++){
        arr[i] = TimeSpan(-(i*i), -(i * i), -(i * i));
        sec[i] = (i*i * 3600) + ( i * i* 60 +(i * i));
    }
    for (int i = 0; i < kArraySize; i++){
        cout<< arr[i] << endl;
        TimeSpan apple(sec[i]);
        arr[i] -= apple;
        cout<< arr[i] << endl;
        cout << endl;
    }
    cout <<"***************    should be zero     ***********" << endl;
    for (int i = 0; i < kArraySize; i++){
        arr[i] = TimeSpan((i*i), (i * i), (i * i));
        sec[i] = (i*i * 3600) + ( i * i* 60 +(i * i));
    }
    for (int i = 0; i < kArraySize; i++){
        TimeSpan apple(sec[i]);
        arr[i] -= apple;
        cout<< arr[i] << endl;
       
    }
    cout << endl;

    cout<< "****************Comparsion Operators*************" << endl;

   for (int i = 0; i < 10; i++){
       arr[i] = TimeSpan(i*i, i * i, i * i);
       sec[i] = i*i * 3600 + i * i* 60 + i * i;
   }
    for (int i = 11; i < kArraySize; i++){
       arr[i] = TimeSpan(-i*i, -i * i, i * i);
       sec[i] = i*i * 3600 + i * i* 60 + i * i;
   }
    for (int i = 10; i < 20; i++){
        cout << arr[i] << endl;
    }

    cout<< "True  == " << status(arr[1] == arr[1]) << endl;
    cout<< "False == " << status(arr[1] == arr[2]) << endl;
    cout<< "True  == " << status(arr[11] == arr[11]) << endl;
    cout<< "False == " << status(arr[11] == arr[12]) << endl;
    cout << endl;
    cout<< "False != " << status(arr[1] != arr[1]) << endl;
    cout<< "True  != " << status(arr[1] != arr[2]) << endl;
    cout<< "False != " << status(arr[11] != arr[11]) << endl;
    cout<< "True  != " << status(arr[11] != arr[12]) << endl;

    cout << endl;
    cout<< "False > " << status(arr[1] > arr[1]) << endl;
    cout<< "True  > " << status(arr[3] > arr[2]) << endl;
    cout<< "False > " << status(arr[11] > arr[11]) << endl;
    cout<< "True  > " << status(arr[11] > arr[12]) << endl;
    cout<< "False > " << status(arr[12] > arr[11]) << endl;

    cout << endl;
    cout<< "True  >= " << status(arr[1] >= arr[1]) << endl;
    cout<< "True  >= " << status(arr[3] >= arr[2]) << endl;
    cout<< "True  >= " << status(arr[11] >= arr[11]) << endl;
    cout<< "True  >= " << status(arr[3] >= arr[3]) << endl;
    cout<< "True  >= " << status(arr[11] >= arr[12]) << endl;
    cout<< "False  >= " << status(arr[12] >= arr[11]) << endl;
    cout<< "True  >= " << status(arr[10] >= arr[11]) << endl;
    TimeSpan ge = arr[11];
    TimeSpan ge1(0.49999999);
    ge += ge1;
    cout << ge1 << endl;
    cout<< "True  == " << status(arr[11] == ge) << endl;
    cout<< "True  >= " << status(arr[11] >= ge) << endl;
    cout<< "False >= " << boolalpha << (arr[12] >= arr[11]) << endl;


    cout<< "True  >" << status(arr[11] > arr[12]) << endl;
    cout<< "False  > " << status(arr[1] > arr[1]) << endl;
    cout<< "False > " << boolalpha << (arr[12] > arr[11]) << endl;
    cout<< "True  > " << boolalpha << (arr[1] > arr[11]) << endl;
    cout<< "False > " << boolalpha << (arr[12] > arr[11]) << endl;
    cout<< "True  > " << boolalpha << (arr[1] > arr[11]) << endl;
    cout<< "False  > " << boolalpha << (arr[11] > arr[1]) << endl;
    cout<< "False  > " << boolalpha << (arr[1] > arr[1]) << endl;


   cout<< "True  <  " << status(arr[11] < arr[10]) << endl;
   cout<< "False  < " << status(arr[1] < arr[1]) << endl;
   cout<< "False  < " << boolalpha << (arr[1] < arr[12]) << endl;
   cout<< "True  <  " << boolalpha << (arr[1] < arr[9]) << endl;
   cout<< "False <  " << boolalpha << (arr[12] < arr[13]) << endl;
   cout<< "True  <  " << boolalpha << (arr[1] < arr[2]) << endl;
    cout<< "false  <  " << boolalpha << (arr[1] < arr[1]) << endl;

    cout<< "True  <= " << status(arr[12] <= arr[11]) << endl;
    cout<< "True  <= " << status(arr[12] <= arr[11]) << endl;
    cout<< "True  <= " << status(arr[12] <= arr[12]) << endl;
    cout<< "False  <= " << status(arr[11] <= arr[12]) << endl;
    cout<< "False  <= " << status(arr[5] <= arr[4]) << endl;
    cout<< "False  <= " << status(arr[5] <= arr[4]) << endl;
    cout<< "False  <= " << status(arr[15] <= arr[16]) << endl;



    return 0;
}

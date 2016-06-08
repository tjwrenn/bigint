# bigint
implementation of a big Integer class written in c++ utilizing methods from the STL

Description
   This project is an implementation of a big Integer class written in c++ utilizing methods from the STL. The underlying container can be specified by the user, but is recommended only for use with vectors and deques. I took extra time to implement the multiplication and long-division operations non-naïvely (without repeated addition and subtraction) and gained quite a bit of performance on pow and gcd because of that. Pow is particularly fast due to its divide and conquer nature. Moreover, the -= and += operations are split up in a case by case manner handling positive addend negative addend, negative addend negative addend, etc to gain speed. I realized that doing sign checks in the underlying forloops would cost a lot.

I decided that it would be better to have the begin iterator point at the most significant digit and contrarily have the end iterator point one past the least significant digit. Furthermore, it was deemed better for ("") to be considered an invalid argument into the constructor and do not assume it to be zero. Leading zeros are allowed to be passed into the constructor but they are immediately discarded. 

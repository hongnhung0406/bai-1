#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;
#define eps 1e-5 //Định nghĩa độ chính xác của phép tính

double tinh (double x) //Input: x. Output: kết quả của sin(x)
//Dùng để tính sin(x) sử dụng khai triển chuỗi Taylor, sử dụng vòng lặp để tính số hạng tiếp theo rồi cộng dồn vào tổng, i tăng lên 2 khi vòng lặp kết thúc.
//Khi giá trị tuyệt đối của số hạng nhỏ hơn eps thì dừng vòng lặp
//Hàm trả về giá trị sin(x)
{
    double S=x, t=x;
    int i=3;

    while (fabs(t)>eps){
        t *= -x*x/(i*(i-1)); //Tính số hạng tiếp theo với công thức Taylor
        S+=t; //Cộng dồn vào tổng S
        i+=2; //i tăng lên 2 sau mỗi vòng lặp
    }
    return S;
}
int main ()
{
    double x;
    cout<<"Nhap x (radian): ";
    cin>>x;
    cout<<fixed<<setprecision(5)<<"Ket qua: "<<tinh(x); //sin(x) được xuất ra với 5 số sau dấu phẩy

    return 0;
}

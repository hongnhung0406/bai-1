#include <iostream>
using namespace std;

bool nhuan (int nam) //Input: năm được nhập vào. Output: true/false
//Kiểm tra có phải năm nhuận hay không
{
    return (nam%4==0 && nam%100!=0) || (nam%400==0);
}

void ketiep (int ngay, int thang, int nam) //Input: ngày, tháng, năm. Output: ngày kế tiếp của ngày, tháng, năm đó
//Tính ngày kế tiếp bằng cách tăng ngày lên 1
//Nếu là ngày 31/12 thì chuyển sang ngày 1/1 năm tiếp theo
//Nếu là ngày cuối cùng của tháng thì xuất ngày 1 của tháng tiếp theo
{
    int tinh [12]={31,28,31,30,31,30,31,31,30,31,30,31};
    if (nhuan(nam)){
        tinh[1]=29;
    }
    if (ngay==tinh[thang-1]){
        ngay=1;
        if (thang==12){
            thang=1;
            nam++;
        }
        else {
            thang++;
        }
    }
    else {
        ngay++;
    }
    cout<<"Ngay ke tiep la: "<<ngay<<"/"<<thang<<"/"<<nam<<endl;
}

void ngaytruoc (int ngay, int thang, int nam) //Input: ngày, tháng, năm. Output: ngày trước đó của ngày, tháng, năm đó
//Tìm ngày trước đó của ngày nhập vào bằng cách giảm ngày đi 1
//Nếu là ngày 1/1 thì chuyển về ngày 31/12 năm trước đó
//Nếu là ngày đầu tiên của tháng thì chuyển sang ngày cuối cùng của tháng trước
{
    int tinh [12]={31,28,31,30,31,30,31,31,30,31,30,31};
    if (nhuan(nam)){
        tinh[1]=29;
    }
    if (ngay==1){
        if (thang==1){
            ngay=31;
            thang=12;
            nam--;
        }
        else {
            thang--;
            ngay=tinh[thang-1];
        }
    }
    else {
        ngay--;
    }
    cout<<"Ngay truoc do la: "<<ngay<<"/"<<thang<<"/"<<nam<<endl;
}

void baonhieu (int ngay, int thang, int nam) ////Input: ngày, tháng, năm. Output: ngày đó là ngày thứ bao nhiêu trong năm
//Tính xem ngày nhập vào là ngày thứ bao nhiêu trong năm bằng vòng lặp, cộng ngày đã cho với tổng số ngày của các tháng trước
{
    int tinh [12]={31,28,31,30,31,30,31,31,30,31,30,31};
    if (nhuan(nam)){
        tinh[1]=29;
    }
    int n=ngay;
    for (int i=0; i<thang-1; i++){
        n+=tinh[i];
    }
    cout<<"Ngay "<<ngay<<"/"<<thang<<"/"<<nam<<" la ngay thu "<<n<<" trong nam"<<endl;
}

int main ()
{
    int ngay, thang, nam;
    int tinh [12]={31,28,31,30,31,30,31,31,30,31,30,31}; //khởi tạo mảng chứa số ngày trong từng tháng của năm không nhuận

    do {
    cout<<"Nhap ngay: ";
    cin>>ngay;
    } while (ngay<=0 || ngay>31);

    do {
    cout<<"Nhap thang: ";
    cin>>thang;
    } while (thang<=0 || thang>12);

    do {
    cout<<"Nhap nam: ";
    cin>>nam;
    } while (nam<=0);

    if (nhuan(nam)){
        tinh[1]=29; //Nếu là năm nhuận thì tháng 2 có 29 ngày
    }

    while(ngay>tinh[thang-1]){
        cout<<"Ngay khong ton tai. Nhap lai ngay: ";
        cin>>ngay;
    }

    ketiep(ngay,thang,nam);
    ngaytruoc(ngay,thang,nam);
    baonhieu(ngay,thang,nam);

    return 0;
}


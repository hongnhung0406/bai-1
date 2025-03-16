#include <iostream>
using namespace std;

struct PHANSO //Định nghĩa kiểu dữ liệu phân số
{
    int tu, mau;
};

int TimUCLN (int a, int b) //Tìm UCLN của 2 mẫu số để rút gọn
{
    int ucln;
    a = a<0 ? -a : a;
    b = b<0 ? -b : b;
    if (a==0 && b==0){
        ucln=0;
    }
    else if (a==0 || b==0){
        ucln=a+b;
    }
    else {
        while (a!=b){
            if (a>b){
                a-=b;
            }
            else {
                b-=a;
            }
        }
        ucln=a;
    }
    return ucln;
}

void Nhap (PHANSO &ps) //Nhâp tử số và mẫu số, nếu mẫu bằng 0 thì yêu cầu nhập lại
{
    cout<<"Nhap tu so: ";
    cin>>ps.tu;
    do
    {
        cout<<"Nhap mau so khac 0: ";
        cin>>ps.mau;
    } while (ps.mau==0);
}

void RutGon (PHANSO &ps)//Chia tử và mẫu cho UCLN đã tìm được để rút gọn phân số
{
    int ucln=TimUCLN(ps.tu,ps.mau);
    if (ucln>0){
        ps.tu/=ucln;
        ps.mau/=ucln;
    }
}

void Xuat (PHANSO ps) //Rút gọn phân số thông qua hàm rút gọn, xuất ra phân số theo đúng định dạng
{
    RutGon(ps);
    if (ps.mau<-1){
        cout<<-ps.tu<<"/"<<-ps.mau;
    }
    else if (ps.mau==-1) {
        cout<<-ps.tu;
    }
    else if (ps.mau==0){
        cout<<"Khong xac dinh";
    }
    else if (ps.mau==1){
        cout<<ps.tu;
    }
    else {
        cout<<ps.tu<<"/"<<ps.mau;
    }
}

int main()
{
    PHANSO ps;
    Nhap(ps);
    Xuat(ps);

    return 0;
}

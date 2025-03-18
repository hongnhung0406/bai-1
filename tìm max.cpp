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

void Nhap (PHANSO &ps) //Nhâp tử số và mẫu số, nếu nhập sai yêu cầu thì yêu cầu nhập lại
{
    cout<<"Nhap tu so: ";
    cin>>ps.tu;
    do
    {
        cout<<"Nhap mau so khac 0: ";
        cin>>ps.mau;
    } while (ps.mau==0);
}

void RutGon (PHANSO &ps) //Tìm UCLN của tử và mẫu, sau đó chia cả hai để rút gọn phân số
//Input: phân số chưa được rút gọn. //Output: phân số đã được rút gọn
{
    int ucln=TimUCLN(ps.tu,ps.mau);
    if (ucln>0){
        ps.tu/=ucln;
        ps.mau/=ucln;
    }
}

PHANSO TimMax (PHANSO ps1, PHANSO ps2) //Rút gọn 2 phân số trước khi sao sánh, thực hiện nhân chéo tử và mẫu để xác định phân số lớn hơn, sau đó xuất ra phân số lớn nhất, nếu 2 phân số bằng nhau thì xuất phân số thứ nhất
//Input: 2 phân số được nhập vào. Output: Phân số lớn nhất
{
    RutGon(ps1);
    RutGon(ps2);
    PHANSO psmax;
    if (ps1.tu*ps2.mau > ps1.mau*ps2.tu){
        psmax=ps1;
    }
    else if (ps1.tu*ps2.mau == ps2.tu*ps1.mau){
        cout<<"Hai phan so bang nhau =";
        psmax=ps1;
    }
    else {
        psmax=ps2;
    }
    return psmax;
}

void Xuat (PHANSO ps) //Rút gọn phân số trước khi xuất, xuất ra phân số theo đúng định dạng
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
    PHANSO ps1,ps2;
    cout<<"Nhap phan so thu nhat: "<<endl;
    Nhap(ps1);
    cout<<"Nhap phan so thu hai: "<<endl;
    Nhap(ps2);
    cout<<"Phan so lon nhat: ";
    Xuat(TimMax(ps1,ps2)); //Xuất ra phân số lớn nhất

    return 0;
}

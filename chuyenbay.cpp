#include <iostream>
#include <string>
#include <cctype>
using namespace std;

struct NGAYBAY //Khởi tạo struct để lưu thông tin ngày, tháng, năm bay
{
    int ngay, thang, nam;
};

struct GIOBAY //Khởi tạo struct để lưu thông tin giờ, phút bay
{
    int gio,phut;
};

struct CHUYENBAY //Lưu thông tin mã, ngày bay, giờ bay, nơi đi, nơi đến của 1 chuyến bay
{
    string ma;
    NGAYBAY nb;
    GIOBAY gb;
    string noidi, noiden;
};

struct MANGCHUYENBAY //Lưu danh sách n chuyến bay
{
    CHUYENBAY *cb;
    int n;
};

bool chu (string s) //Kiểm tra độ hợp lệ của mã chuyến bay
//Mã chuyến bay phải ngắn hơn 5 kí tự, chỉ chứa chữ cái hoặc số, không được chứa dấu cách hoặc kí tự đặc biệt
{
    if (s.length()>5) return false;
    for (char c : s){
        if (!isalnum(c)) return false;
    }
    return true;
}

bool nhuan (int nam) //Hàm kiểm tra năm nhập vào có phải năm Nhuận hay không
{
    return (nam%400==0) || (nam%4==0 && nam%100!=0);
}

bool kiemtra (int ngay, int thang, int nam) //Hàm kiểm tra ngày, tháng, năm nhập vào có hợp lệ hay không
{
    if (nam<1) return false; //Năm phải lớn hơn 0
    if (thang<1 || thang>12) return false; //Tháng từ 1-12
    int tinh[12]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; //Biến để lưu tổng số ngày của mỗi tháng
    if (nhuan(nam)){
        tinh[1]=29; //Nếu là năm Nhuận thì tháng 2 có 29 ngày
    }
    return (ngay>0 && ngay<=tinh[thang-1]);
}

bool gio (int gio, int phut) //Hàm kiểm tra giờ bay có hợp lệ hay không, giờ trong khoảng [0,23], phút trong khoảng [0-59];
{
    return (gio>=0 && gio<=23 && phut>=0 && phut<=59);
}

bool kt (string s) //Hàm kiểm tra tính hợp lệ của nơi đi, nơi đến
//Nơi đi, nơi đến phải không quá 20 kí tự, chỉ chứa chữ cái và dấu cách, không chứa số và kí tự đặc biệt
{
    if (s.length()>20) return false;
    for (char c : s){
        if (!isalpha(c) && c!=' ') return false;
    }
    return true;
}

void Nhap (CHUYENBAY &cb) //Hàm nhập thông tin của một chuyến bay
{
    do {
        cout<<"Nhap ma chuyen bay hop le, dai toi da 5 ki tu: ";
        cin>>cb.ma;
    } while (!chu(cb.ma));
    do {
        cout<<"Nhap ngay bay: ";
        cin>>cb.nb.ngay;
        cout<<"Nhap thang bay: ";
        cin>>cb.nb.thang;
        cout<<"Nhap nam bay: ";
        cin>>cb.nb.nam;
    } while(!kiemtra(cb.nb.ngay,cb.nb.thang,cb.nb.nam));
    do {
        cout<<"Nhap gio bay: ";
        cin>>cb.gb.gio;
        cout<<"Nhap phut bay: ";
        cin>>cb.gb.phut;
    } while(!gio(cb.gb.gio,cb.gb.phut));
    cin.ignore();
    do {
        cout<<"Nhap noi di: ";
        getline(cin,cb.noidi);
    } while (!kt(cb.noidi));
    do {
        cout<<"Nhap noi den: ";
        getline(cin,cb.noiden);
    } while(!kt(cb.noiden));
}

void Nhap (MANGCHUYENBAY &mcb) //Nhập số n chuyến bay
{
    do {
        cout<<"Nhap so luong chuyen bay: ";
        cin>>mcb.n;
    } while (mcb.n<=0);
    mcb.cb = new CHUYENBAY[mcb.n];
    for (int i=0; i<mcb.n; i++){
        cout<<"Nhap chuyen bay thu "<<i+1<<": "<<endl;
        Nhap(mcb.cb[i]);
    }
}

void thuong (string &s) //Hàm chuyển tất cả chữ viết hoa thành chữ thường
{
    for (char &c : s){
        c=tolower(c);
    }
}

void Xuat (CHUYENBAY cb) //Hàm xuất thông tin của một chuyến bay
{
    cout<<"Ma chuyen bay: "<<cb.ma<<endl;
    cout<<"Ngay bay: "<<cb.nb.ngay<<"/"<<cb.nb.thang<<"/"<<cb.nb.nam<<endl;
    cout<<"Gio bay: "<<cb.gb.gio<<" gio "<<cb.gb.phut<<" phut"<<endl;
    cout<<"Noi di: "<<cb.noidi<<endl;
    cout<<"Noi den: "<<cb.noiden<<endl;
}

void Xuat (MANGCHUYENBAY mcb) //Hàm xuất n chuyến bay
{
    for (int i=0; i<mcb.n; i++){
        Xuat(mcb.cb[i]);
    }
    cout<<endl;
}

void timkiem (MANGCHUYENBAY mcb) //Hàm tìm kiếm chuyến bay theo mã, nơi đi hoặc nơi đến
//Chuyển tất cả mã, nơi đi, nơi đến thành chữ thường để tìm kiếm không phân biệt chữ hoa, chữ thường
//Sử dụng find để kiểm tra xem mã, nơi đi, nơi đến có xuất hiện không
{
    string tim;
    cout<<"\n-----TIM KIEM CHUYEN BAYY-----"<<endl;
    cout<<"Nhap ma chuyen bay, noi di hoac noi den can tim kiem: ";
    getline(cin,tim);
    thuong(tim);
    bool found=false;
    for (int i=0; i<mcb.n; i++){
        string ma=mcb.cb[i].ma;
        string noidi=mcb.cb[i].noidi;
        string noiden=mcb.cb[i].noiden;
        thuong(ma);
        thuong(noidi);
        thuong(noiden);
        if (ma.find(tim)!=string::npos || noidi.find(tim)!=string::npos ||noiden.find(tim)!=string::npos){
            found=true;
            Xuat(mcb.cb[i]);
        }
    }
    if (!found){
        cout<<"Khong co chuyen bay hop le"; //Nếu không có chuyến bay tương ứng thì xuất thông báo không tìm thấy
    }
}

void sapxep (MANGCHUYENBAY &mcb) //Sắp xếp danh sách chuyến bay theo thứ tự thời gian từ sớm đến muộn
{
    cout<<"\n-----DANH SACH CHUYEN BAY DA DUOC SAP XEP-----"<<endl;
    CHUYENBAY temp;
    for (int i=0; i<mcb.n-1; i++){
        for (int j=i+1; j<mcb.n; j++){
            if (mcb.cb[i].nb.nam>mcb.cb[j].nb.nam ||
                (mcb.cb[i].nb.nam==mcb.cb[j].nb.nam && mcb.cb[i].nb.thang>mcb.cb[j].nb.thang) ||
                 (mcb.cb[i].nb.nam==mcb.cb[j].nb.nam && mcb.cb[i].nb.thang==mcb.cb[j].nb.thang && mcb.cb[i].nb.ngay>mcb.cb[j].nb.ngay) ||
                    (mcb.cb[i].nb.nam==mcb.cb[j].nb.nam && mcb.cb[i].nb.thang==mcb.cb[j].nb.thang && mcb.cb[i].nb.ngay==mcb.cb[j].nb.ngay && mcb.cb[i].gb.gio>mcb.cb[j].gb.gio) ||
                        (mcb.cb[i].nb.nam==mcb.cb[j].nb.nam && mcb.cb[i].nb.thang==mcb.cb[j].nb.thang && mcb.cb[i].nb.ngay==mcb.cb[j].nb.ngay && mcb.cb[i].gb.gio==mcb.cb[j].gb.gio && mcb.cb[i].gb.phut>mcb.cb[j].gb.phut)) {
                temp=mcb.cb[i];
                mcb.cb[i]=mcb.cb[j];
                mcb.cb[j]=temp;
            }
        }
    }
}

void tk (MANGCHUYENBAY mcb) //Hàm tìm kiếm các chuyến bay khởi hành từ 1 nơi cụ thể trong 1 ngày được chỉ định
//So sánh ngày với dữ liệu nhập vào
{
    string place;
    int ngay,thang,nam;
    cout<<"-----TIM KIEM CHUYEN BAY-----"<<endl;
    cout<<"Nhap noi khoi hanh: ";
    getline(cin,place);
    thuong(place); //Đưa về chữ thường để tìm kiếm
    do {
        cout<<"Nhap ngay khoi hanh: ";
        cin>>ngay;
        cout<<"Nhap thang khoi hanh: ";
        cin>>thang;
        cout<<"Nhap nam khoi hanh: ";
        cin>>nam;
    } while(!kiemtra(ngay,thang,nam));

    bool found=false;
    for (int i=0; i<mcb.n; i++){
        string diadiem=mcb.cb[i].noidi;
        thuong(diadiem); //Đưa về chữ thường để tìm kiếm

        if (diadiem.find(place)!=string::npos && mcb.cb[i].nb.ngay==ngay && mcb.cb[i].nb.thang==thang && mcb.cb[i].nb.nam==nam){
            found=true;
            Xuat(mcb.cb[i]);
        }
    }
    if (!found){
        cout<<"Khong co chuyen bay hop le"<<endl;
    }
}

void dem (MANGCHUYENBAY mcb) //Hàm đếm số lượng chuyến bay từ một nơi đi đến một nơi đến nhất định
//Đưa tất cả nơi đi, nơi đến về dạng chữ viết thường để tìm kiếm
//Kiểm tra địa điểm nhập vào có giống với danh sách không
{
    string di;
    string den;
    cout<<"\n-----TONG SO CHUYEN BAY CAN TIM KIEM-----"<<endl;
    cout<<"Nhap noi di muon tim kiem: ";
    cin.ignore();
    getline(cin,di);
    cout<<"Nhap noi den muon tim kiem: ";
    getline(cin,den);
    int dem=0;
    bool found=false;
    for (int i=0; i<mcb.n; i++){
        string noidi=mcb.cb[i].noidi;
        string noiden=mcb.cb[i].noiden;
        thuong(noidi);
        thuong(noiden);

        if (noidi.find(di)!=string::npos && noiden.find(den)!=string::npos){
            found=true;
            dem++;
        }
    }
    if (dem==0){
        cout<<"Khong co chuyen bay hop le";
    }
    else {
        cout<<"Co "<<dem<<" chuyen bay tu "<<di<<" den "<<den; //Xuất ra tổng số chuyến bay tìm được
    }

}

int main ()
{
    MANGCHUYENBAY mcb;
    Nhap(mcb);
    timkiem(mcb);
    sapxep(mcb);
    Xuat(mcb);
    tk(mcb);
    dem(mcb);

    return 0;
}

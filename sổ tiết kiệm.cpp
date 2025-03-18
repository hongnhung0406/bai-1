#include <iostream>
#include <string>
#include <cctype>
#include <ctime>
#include <iomanip>
using namespace std;

struct DATE ////Khởi tạo struct để lưu thông tin ngày, tháng, năm mở sổ
{
    int ngay,thang,nam;
};

struct TIETKIEM //Lưu thông tin mã, loại sổ, họ tên, cmnd, DATE, số tiền gửi của một sổ tiết kiệm
{
    string ma, loai, name, cmnd;
    DATE ngth;
    double money;
};

struct MANGTIETKIEM //Lưu danh sách n sổ tiết kiệm
{
    TIETKIEM *tk;
    int n;
};

bool ktma (string s)//Kiểm tra độ hợp lệ của mã sổ
//Mã sổ phải nhỏ hơn 5 kí tự, chỉ chứa chữ cái hoặc số, không được chứa dấu cách hoặc kí tự đặc biệt
{
    if (s.empty() || s.length()>5) return false;
    for (char c : s){
        if (!isalnum(c) || c==' ') return false;
    }
    return true;
}

bool ktloai (string s) //Kiểm tra độ hợp lệ của loại sổ
//Loại phải ngắn hơn 10 kí tự, chỉ chứa chữ cái và dấu cách, không được chứa số và kí tự đặc biệt
{
    if (s.empty() || s.length()>10) return false;
    for (char c : s){
        if (!isalpha(c) && c!=' ') return false;
    }
    return true;
}

bool ktname (string s) //Kiểm tra độ hợp lệ của họ tên
//Họ tên phải ngắn hơn 30 kí tự, chỉ chứa chữ cái và dấu cách, không được chứa số hoặc kí tự đặc biệt
{
    if (s.empty() || s.length()>30) return false;
    for (char c : s){
        if (!isalpha(c) && c!=' ') return false;
    }
    return true;
}

bool ktcmnd (string s) //Kiểm tra độ hợp lệ của cmnd
//CMND phải bằng 9 hoặc 12 số, chỉ chứa số, không được chứa dấu cách hoặc chữ cái, kí tự đặc biệt
{
    if (s.length()!=9 && s.length()!=12) return false;
    for (char c : s){
        if (!isdigit(c)) return false;
    }
    return true;
}

bool nhuan (int nam) //Hàm kiểm tra năm nhập vào có phải năm Nhuận hay không
{
    return (nam%400==0 || nam%4==0 && nam%100!=0);
}

bool kiemtra (int ngay, int thang, int nam) //Hàm kiểm tra ngày, tháng, năm nhập vào có hợp lệ hay không
{
    if (nam<1) return false;
    if (thang<1 || thang>12) return false;
    int tinh[12]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (nhuan(nam)){
        tinh[1]=29;
    }
    return (ngay>0 && ngay<=tinh[thang-1]);
}

void Nhap (TIETKIEM &tk) //Hàm nhập thông tin của một sổ tiết kiệm
{
    do {
        cout<<"Nhap ma so hop le, dai toi da 5 ki tu: ";
        cin>>tk.ma;
    } while (!ktma(tk.ma));

    cin.ignore();
    do {
        cout<<"Nhap loai tiet dai toi da 10 ki tu (ngan han, dai han): ";
        getline(cin,tk.loai);
    } while(!ktloai(tk.loai));

    do {
        cout<<"Nhap ho ten khach hang, dai toi da 30 ki tu: ";
        getline(cin,tk.name);
    } while (!ktname(tk.name));

    do {
        cout<<"Nhap chung minh nhan dan: ";
        cin>>tk.cmnd;
    } while(!ktcmnd(tk.cmnd));

    do {
        cout<<"Nhap ngay/thang/nam mo so: ";
        cin>>tk.ngth.ngay>>tk.ngth.thang>>tk.ngth.nam;
    } while(!kiemtra(tk.ngth.ngay,tk.ngth.thang,tk.ngth.nam));

    do {
        cout<<"Nhap so tien gui: ";
        cin>>tk.money;
    } while(tk.money<0);
}

void Nhap (MANGTIETKIEM &mtk) //Nhập số n sổ tiết kiệm
{
    do {
        cout<<"Nhap so luong so tiet kiem: ";
        cin>>mtk.n;
    } while(mtk.n<=0);

    mtk.tk = new TIETKIEM[mtk.n];
    for (int i=0; i<mtk.n; i++){
        cout<<"Nhap so tiet kiem thu "<<i+1<<": "<<endl;
        Nhap(mtk.tk[i]);
    }
}

void Xuat (TIETKIEM tk) //Hàm xuất thông tin của một sổ tiết kiệm
{
    cout<<"Ma so: "<<tk.ma<<endl;
    cout<<"Loai tiet kiem: "<<tk.loai<<endl;
    cout<<"Ho ten khach hang: "<<tk.name<<endl;
    cout<<"CMND: "<<tk.cmnd<<endl;
    cout<<"Ngay mo so: "<<tk.ngth.ngay<<"/"<<tk.ngth.thang<<"/"<<tk.ngth.nam<<endl;
    cout<<"So tien gui: "<<fixed<<setprecision(0)<<tk.money<<endl;
}

void Xuat (MANGTIETKIEM mtk) //Hàm xuất n sổ
{
    for (int i=0; i<mtk.n; i++){
        Xuat(mtk.tk[i]);
    }
    cout<<endl;
}

void thuong (string &s) //Hàm chuyển tất cả chữ viết hoa thành chữ thường
{
    for (char &c : s){
        c=tolower(c);
    }
}

void timkiem (MANGTIETKIEM mtk) //Hàm tìm kiếm sổ theo cmnd hoặc mã sổ
//Chuyển tất cả mã thành chữ thường để tìm kiếm không phân biệt chữ hoa, chữ thường
//Sử dụng gound để kiểm tra xem mã, nơi đi, nơi đến có xuất hiện không
{
    string tim;
    cout<<"Nhap so CMND hoac ma so de tim kiem so tiet kiem: ";
    cin>>tim;
    thuong(tim);
    bool found=false;
    for (int i=0; i<mtk.n; i++){
        string cmnd = mtk.tk[i].cmnd;
        string ma = mtk.tk[i].ma;
        thuong (cmnd);
        thuong(ma);
        if (cmnd.find(tim)!=string::npos || ma.find(tim)!=string::npos){
            found=true;
            Xuat(mtk.tk[i]);
        }
    }
    if (!found){
        cout<<"Khong tim thay so tiet kiem phu hop";
    }
}

void tim (MANGTIETKIEM mtk) //Hàm tìm kiếm các sổ tiết kiệm trong 1 ngày được chỉ định
//So sánh ngày với dữ liệu nhập vào
{
    cout<<"\-----TIM KIEM SO THEO NGAY THANG NAM-----"<<endl;
    int ngay,thang,nam;
    do {
        cout<<"Nhap ngay mo so: ";
        cin>>ngay;
        cout<<"Nhap thang mo so: ";
        cin>>thang;
        cout<<"Nhap nam mo so: ";
        cin>>nam;
    } while(!kiemtra(ngay,thang,nam));
    bool found=false;
    for (int i=0; i<mtk.n; i++){
        if(mtk.tk[i].ngth.ngay==ngay && mtk.tk[i].ngth.thang==thang && mtk.tk[i].ngth.nam==nam){
            found=true;
            Xuat(mtk.tk[i]);
        }
    }
    if (!found){
        cout<<"Khong co so tiet kiem hop le";
    }
}

void sapxep (MANGTIETKIEM mtk) //Sắp xếp danh sách sổ theo thứ tự số tiền gửi giảm dần
{
    cout<<"\n-----DANH SACH DUOC SAP XEP THEO SO TIEN GUI GIAM DAN-----"<<endl;
    TIETKIEM temp;
    for (int i=0; i<mtk.n-1; i++){
        for (int j=i+1; j<mtk.n; j++){
            if (mtk.tk[i].money<mtk.tk[j].money){
                temp=mtk.tk[i];
                mtk.tk[i]=mtk.tk[j];
                mtk.tk[j]=temp;
            }
        }
    }
}

void sx (MANGTIETKIEM mtk) //Sắp xếp danh sách sổ tiết kiệm theo thứ tự thời gian từ sớm đến muộn
{
    cout<<"-----DANH SACH DUOC SAP XEP THEO NGAY MO SO TANG DAN-----"<<endl;
    TIETKIEM temp;
    for (int i=0; i<mtk.n-1; i++){
        for (int j=i+1; j<mtk.n; j++){
            if (mtk.tk[i].ngth.nam>mtk.tk[j].ngth.nam ||
                mtk.tk[i].ngth.nam==mtk.tk[j].ngth.nam && mtk.tk[i].ngth.thang>mtk.tk[j].ngth.thang ||
                mtk.tk[i].ngth.nam==mtk.tk[j].ngth.nam && mtk.tk[i].ngth.thang==mtk.tk[j].ngth.thang && mtk.tk[i].ngth.ngay>mtk.tk[j].ngth.ngay) {
                    temp=mtk.tk[i];
                    mtk.tk[i]=mtk.tk[j];
                    mtk.tk[j]=temp;
                }
        }
    }
}

int tinhngay (DATE d1, DATE d2) //Hàm tính số ngày từ ngày gửi đến ngày hiện tại
{
    struct tm time1 = {0,0,12, d1.ngay, d1.thang-1, d1.nam-1900};
    struct tm time2 = {0,0,12, d2.ngay, d2.thang-1, d2.nam-1900};

    time_t t1 = mktime(&time1);
    time_t t2 = mktime(&time2);

    return (t2-t1)/(60*60*24);
}

void laisuat (MANGTIETKIEM &mtk, DATE today, double lsngan, double lsdai) //Hàm tính lãi suất dựa trên loại sổ dài hạn hay ngắn hạn
{
    cout<<"----SO TIET KIEM SAU KHI TINH LAI SUAT----"<<endl;
    for (int i=0; i<mtk.n; i++){
        int songay = tinhngay(mtk.tk[i].ngth,today);
        double tienlai=0;

        if (mtk.tk[i].loai=="ngan han" && songay<=180){
            tienlai = mtk.tk[i].money * (lsngan/100) * (songay/365.0);
        }
        else if (mtk.tk[i].loai=="dai han" && songay>180){
            tienlai = mtk.tk[i].money * (lsdai/100) * (songay/365.0);
        }
        else {
            cout<<"Loai tiet kiem khong phu hop voi thoi gian gui"<<endl; //Nếu loại dài hạn có số ngày<180 hoặc loại ngắn hạn có số ngày >180 thì báo lỗi
            continue;
        }
        Xuat(mtk.tk[i]);
        cout<<"Lai suat: "<<fixed<<setprecision(0)<<tienlai<<endl;
    }
}

double tinhlai (TIETKIEM tk, double lsngan, double lsdai, DATE today) //Tính số tiền lãi dựa trên loại sổ
{
    int songay = tinhngay(tk.ngth,today);
    double lsthap = (tk.loai=="ngan han") ? (lsngan*0.5) : (lsdai*0.5);
    double laisuat = (tk.loai=="ngan han" && songay<180) || (tk.loai=="dai han" && songay<365) ? lsthap : (tk.loai=="ngan han") ? lsngan : lsdai;
    return tk.money * (laisuat/100) * (songay/365.0);
}

void ruttien (MANGTIETKIEM &mtk, TIETKIEM &tk, DATE today, double lsngan, double lsdai) //Hàm giúp người dùng rút tiền, nếu rút tiền trước hạn sẽ báo tính lãi suất thấp hơn
{
    double sotien;
    double tienlai = tinhlai(tk,lsngan,lsdai,today);
    cout<<"Nhap so tien ban muon rut: ";
    cin>>sotien;
    if ((tk.loai=="ngan han" && tinhngay(tk.ngth,today)<180) || (tk.loai=="dai han" && tinhngay(tk.ngth,today)<365)){
        cout<<"Rut truoc han se tinh lai suat thap hon!"<<endl;
    }
    if (sotien > (tk.money+tienlai)){
        cout<<"So du khong du"<<endl;
    } else {
        tk.money = (tk.money+tienlai) - sotien;
        cout<<"Rut tien thanh cong"<<endl;
        cout<<"So tien con lai trong tai khoan: "<<tk.money<<endl;
    }
}

int main ()
{
    MANGTIETKIEM mtk;
    Nhap(mtk);
    Xuat(mtk);

    timkiem(mtk);

    tim(mtk);

    sapxep(mtk);
    Xuat(mtk);

    sx(mtk);
    Xuat(mtk);

    double lsngan,lsdai;
    do {
        cout<<"Nhap lai suat ngan han (%/nam): ";
        cin>>lsngan;
    } while (lsngan<=0);

    do {
        cout<<"Nhap lai suat dai han (%/nam): ";
        cin>>lsdai;
    } while (lsdai<=0);

    time_t now = time(0);
    tm *ltm = localtime(&now);
    DATE today = {ltm->tm_mday, ltm->tm_mon+1, ltm->tm_year+1900};
    laisuat(mtk,today,lsngan,lsdai);

    TIETKIEM *tk;
    string maso;
    cout<<"\n-----CHUONG TRINH RUT TIEN-----"<<endl;
    do {
        cout<<"Nhap ma so tiet kiem muon rut tien: ";
        cin>>maso;
        for (int i=0; i<mtk.n; i++){
            if (mtk.tk[i].ma==maso){
                tk=&mtk.tk[i];
                break;
            }
        }
        if (!tk){
            cout<<"Khong tim thay ma so tiet kiem, vui long nhap lai: ";
        }
    } while (!tk);

    ruttien(mtk,*tk,today,lsngan,lsdai);

    return 0;
}

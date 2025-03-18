#include <iostream>
#include <string>
#include <cctype>
using namespace std;

struct HOCSINH //Khởi tạo struct HOCSINH để lưu thông tin của một học sinh họ tên, điểm Toán, Văn, Anh và điểm tb
{
    string name;
    double toan, van, anh, tb;
};

struct MANGHOCSINH //struct MANGHOCSINH để lưu danh sách n học sinh
{
    HOCSINH *hs;
    int n;
};

bool chu (string s) //Input: họ tên hs. Output: true/falsefalse
//Hàm kiểm tra tính hợp lệ của họ tên
//Học tên phải từ 5-50 kí tự, chỉ chứa chữ cái và dấu cách, không có số hoặc kí tự đặc biệt
{
    if (s.length()<5 || s.length()>50) return false;
    for (char c : s){
        if (!(isalpha(c) || c==' ')) return false;
    }
    return true;
}

void Nhap (HOCSINH &hs) //Hàm nhập thông tin của 1 học sinh
{
    cin.ignore();
    do {
        cout<<"Nhap ho ten hop le: ";
        getline(cin,hs.name);
    } while (!chu(hs.name)); //Nhập họ tên hợp lệ, nếu sai phải nhập lại
    do {
        cout<<"Nhap diem toan: ";
        cin>>hs.toan;
    } while (hs.toan<0 || hs.toan>10); //Nhập điểm toán từ 0-10, nếu sai phải nhập lại
    do {
        cout<<"Nhap diem van: ";
        cin>>hs.van;
    } while (hs.van<0 || hs.van>10); //Nhập điểm văn từ 0-10, nếu sai phải nhập lại
    do {
        cout<<"Nhap diem Ngoai ngu: ";
        cin>>hs.anh;
    } while (hs.anh<0 || hs.anh>10); //Nhập điểm anh từ 0-10, nếu sai phải nhập lại

    hs.tb=(2*hs.toan + hs.van + hs.anh)/4; //Tính điểm trung bình
}

void Nhap (MANGHOCSINH &mhs) //Nhập số n học sinh
{
    do {
        cout<<"Nhap so hoc sinh: ";
        cin>>mhs.n;
    } while (mhs.n<=0);
    mhs.hs=new HOCSINH[mhs.n];
    for (int i=0; i<mhs.n; i++){
        cout<<"Nhap hoc sinh thu "<<i+1<<": "<<endl;
        Nhap(mhs.hs[i]);
    }
}

string xeploai (double tb) //Input: Điểm trung bình. Output: xếp loại học sinhsinh
//Dùng cấu trúc rẽ nhánh để xếp loại học lực cho học sinh dựa trên điểm trung bình
{
    if (tb>=9) return "Xuat sac";
    else if (tb>=8) return "Gioi";
    else if (tb>=6.5) return "Kha";
    else if (tb>=5) return "Trung binh";
    else return "Yeu";
}

void Xuat (HOCSINH hs) //Xuất thông tin của một học sinh
{
    cout<<"Ho ten hoc sinh: "<<hs.name<<endl;
    cout<<"Diem trung binh: "<<hs.tb<<endl;
    cout<<"Xep loai: "<<xeploai(hs.tb)<<endl;
    cout<<endl;
}
void Xuat (MANGHOCSINH mhs) //Xuất danh sách tất cả học sinh
{
    for (int i=0; i<mhs.n; i++){
        Xuat(mhs.hs[i]);
    }
    cout<<endl;
}

void FindMax (MANGHOCSINH mhs) //Input: mảng học sinh. Output: học sinh có điểm trung bình cao nhất
//Tìm học sinh có điểm trung bình lớn nhất bằng vòng lặp for
//Gán max là hs ở vị trí 0, chạy vòng lặp để tìm max tới vị trí cuối cùng
{
    double max=mhs.hs[0].tb;
    for (int i=1; i<mhs.n; i++){
        if (mhs.hs[i].tb>max){
            max=mhs.hs[i].tb;
        }
    }
    cout<<"Danh sach hoc sinh co diem trung binh cao nhat: "<<endl;
    for (int i=0; i<mhs.n; i++){
        if (mhs.hs[i].tb==max){
            Xuat(mhs.hs[i]);
        }
    }
}
void thuong (string &s) //Input: họ tên hs. Output: họ tên hs đã được viết thườngthường
//Hàm để đưa tên học sinh về chữ thường để tìm kiếm
{
    for (char &c : s){
        c=tolower(c);
    }
}

void Findsv (MANGHOCSINH mhs) //Input: họ tên hs cần tìm. Output: thông tin hs cần tìm
//Hàm tìm học sinh theo tên
{
    cin.ignore();
    string tim;
    cout<<"Nhap ten sinh vien can tim: ";
    getline(cin,tim);
    thuong(tim); //Viết thường tên cần tìm
    bool found=false; //Khởi tạo biến found
    for (int i=0 ; i<mhs.n; i++){
        string temp=mhs.hs[i].name;
        thuong(temp);

        if (temp.find(tim) != string::npos){ //Nếu tìm thấy tên học sinh cần tìm, xuất thông tin học sinh đó
            Xuat(mhs.hs[i]);
            found=true;
        }
    }
    if (!found){
        cout<<"Khong co sinh vien can tim trong danh sach"<<endl;
    }
}

void Toan (MANGHOCSINH mhs) //Input: Mảng học sinh. Output: Học sinh có điểm toán cao nhất
//Hàm tìm kiếm học sinh có điểm toán thấp nhất dùng vòng lặp for
//Khởi tạo min là học sinh thứ 0, chạy đến cuối vòng lặp để tìm và xuất min
{
    double min=mhs.hs[0].toan;
    for (int i=1; i<mhs.n; i++){
        if (mhs.hs[i].toan<min){
            min=mhs.hs[i].toan;
        }
    }
    cout<<"Danh sach hoc sinh co diem toan thap nhat: "<<endl;
    for (int i=0; i<mhs.n; i++){
        if (mhs.hs[i].toan==min){
            Xuat(mhs.hs[i]);
        }
    }
}

int main ()
{
    MANGHOCSINH mhs;
    Nhap(mhs);
    cout<<"----DIEM TRUNG BINH VA PHAN LOAI HOC SINH----"<<endl;
    Xuat(mhs);

    cout<<"----TIM KIEM HOC SINH CO DIEM TB CAO NHAT----"<<endl;
    FindMax(mhs);

    cout<<"----TIM KIEM HOC SINH THEO TEN----"<<endl;
    Findsv(mhs);

    cout<<"----TIM KIEM SINH VIEN CO DIEM TOAN THAP NHAT----"<<endl;
    Toan(mhs);

    return 0;
}

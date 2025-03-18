#include <iostream>
using namespace std;

void lientuc (int a[], int b[], int x, int y) //Input: mảng A và B. Output: vị trí xuất hiện của A trong B và số lần xuất hiện
//Dùng vòng lặp for để tìm vị trí xuất hiện của dãy A trong dãy B từ i=0 đến i=y-x
//Mỗi lần A xuất hiện biến đếm được tăng 1
//Nếu đếm > 0 thì xuất số lần xuất hiện của A và vị trí xuất hiện, nếu đếm=0 thì xuất không tìm thấy
{
    cout<<"Voi A = [";
    for (int i=0; i<x; i++){
        cout<<a[i];
        if (i<x-1) cout<<",";
    }
    cout<<"], B = [";
    for (int i=0; i<y; i++){
        cout<<b[i];
        if (i<y-1) cout<<",";
    }
    cout<<"], mang A xuat hien ";
    int dem=0;
    cout<<"tai cac chi so bat dau la ";
    for (int i=0; i<=y-x; i++){
        bool found=true;
        for (int j=0; j<x; j++){
            if (a[j]!=b[i+j]){
                found=false;
                break;
            }
        }
        if (found){
            if (dem>0){
                cout<<", ";
            }
            cout<<i;
            dem++;
        }
    }
            if (dem==0){
        cout<<"...Loi, khong tim thay";
        return;
    }
    else {
        cout<<" voi tan suat "<<dem<<" lan";
    }
}

int main ()
{
    int x,y;
    int a[1000], b[1000];
    cout<<"Nhap so phan tu cua mang A va mang B: ";
    cin>>x>>y;
    cout<<"Nhap cac phan tu cua mang A: ";
    for (int i=0; i<x; i++){
        cin>>a[i];
    }
    cout<<"Nhap cac phan tu cua mang B: ";
    for (int i=0; i<y; i++){
        cin>>b[i];
    }
    lientuc(a,b,x,y);
    return 0;
}

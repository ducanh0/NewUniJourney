/*
code nay de xem muon hoc mon nao thi phai hoc xong cac mon nao khac
tien do hoc tap , % hoan thanh tin chi quy dinh
thong ke cac thanh phan diem (bao nhieu % a, bao nhieu % a+, ...)
nhap ma mon hoc -> ten mon hoc + diem + review mon hoc do
gpa
------------------------
du lieu :
ma hoc phan (string) , ten hoc phan (string), so tin chi (int) , ma hoc phan tien quyet (string)
diem hoc phan (a,b,c,...), review mon hoc (string)
-------------------------------------
yeu cau :
1 la xem gpa (done)
2 la xem mon hoc (ten mon hoc + so tin chi + diem + review)
3 la xem thong ke diem
4 la them mot mon hoc (nhap ma hoc phan , ten hoc phan , nhap diem)
5 la xem neu muon hoc mot mon hoc thi can phai hoc nhung mon hoc nao (tien quyet),
di kem voi do la xem cac mon do da co diem chua (da hoan thanh chua)
6 la xem tien do hoc tap (hoan thanh bao nhieu % tin chi quy dinh)
7 la bo sung review cho mon hoc (review cu + \n + review moi)
---------------------------------------
dinh dang output :
1 la  x.xx
2 la ten mon hoc + diem + \n + review mon hoc
3 la a+ - so mon hoc (int) - % (xx.xx) , a - ...
4 la tra ve "da nhap diem thanh cong , ban co muon nhap review khong ?"
5 la ten mon hoc : da/chua hoc duoc + \n + (mon tien quyet + diem/chua hoc) + \n + ...
6 la so tin chi da hoan thanh / so tin chi quy dinh + xx.xx %
7 la "da nhap review thanh cong"
-------------------------------------------

*/
#include <bits/stdc++.h>

using namespace std;

const int slMonHocCoTheHoc = 80 ;
const int slTinChiCoTheHoc = 151 - 3 - 4 - 8  ;

unordered_map<int, string> intToName;
unordered_map<string, string> nameToname; /// ma hoc phan - ten hoc phan
unordered_map<string, int> nameToInt; /// anh xa thanh int de tim cac mon tien quyet
/// diem chu -> diem so , vd : a+ -> 4.0
unordered_map<string, double> grade;
vector<int> adj[slMonHocCoTheHoc] ;
int ok[slMonHocCoTheHoc], danhDau ; /// dfs de tim cac mon tien quyet
vector<pair< pair<string, string>, pair<int, bool > > > V ; /// luu diem - review tung mon hoc - so tin chi - co bat buoc hoc hay khong
int slMonHoc = 0 , slTinChi = 0 , dem[10] = {0} ; /// gpa = sum / slTinChi , dem[0] = sl a+ , dem[1] = sl a , ...
long double sum  = 0.0;

void xemMonHoc(string maHocPhan){
    ///cout<<1;
    cout << "------------------------\n";
    cout << "Ten mon hoc : " << nameToname[maHocPhan] << "\n" ;

    int id = nameToInt[maHocPhan];
    cout << "So tin chi : " << V[id].second.first << "\n" ;

    cout << "Diem : " << V[id].first.first << "\n" ;

    cout << "Review :" << V[id].first.second << "\n-------------------------------\n" ;
}

void dfs(int u){
    for(int v : adj[u]){
        if(ok[v] != ok[u]){
            ok[v] = ok[u] ;
            dfs(v);
        }
    }
}

void timCacMonTienQuyet(string maHocPhan){
    int u = nameToInt[maHocPhan] ;
    ok[u] = ++danhDau;
    dfs(u) ;

    bool okay = 1 ; /// co du dieu kien hoc mon do hay chua

    for(int i = 0 ; i < slMonHocCoTheHoc ; i ++)
        if((i != u) && (ok[i] == ok[u]))
            okay &= (V[i].first.first != "Chua hoc");

    cout << "Ten mon hoc : " << nameToname[maHocPhan] << "\nKet luan : " << (okay ? "Du " : "Chua du ") << "dieu kien hoc\n" ;
    cout << (V[u].second.second ? "Bat buoc hoc" : "Tu chon") << "\n--------------\n" ;
    cout << "Cac mon hoc tien quyet : \n" ;

    for(int i = 0 ; i < slMonHocCoTheHoc ; i ++)
        if((i != u) && (ok[i] == ok[u]))
            xemMonHoc(intToName[i]);
}

void thongKeDiem(){
    for(int i = 0; i < 9 ; i ++){
        if(i == 0)
            cout << "so luong mon bi diem f la " ;
        else
            cout << "so luong mon bi diem " << char('a' + ((i + bool(i % 2)) / 2 - 1)) << ((i % 2) ? "" : "+") << " la " ;

        cout << dem[i] << ", chiem " << fixed << setprecision(2) << double(dem[i] * 100.0) / slMonHoc << " % \n" ;
   }
   cout << "------------------------\n" ;
}

void xemGPA(){
     cout << "GPA hien tai : " << fixed << setprecision(2) << sum / slTinChi << " " << slTinChi << "\n--------------------\n" ;
}

void tienDoHocTap(){
    cout << "Ban da hoan thanh " << fixed << setprecision(2) << double(slTinChi * 100.0) / slTinChiCoTheHoc << " % chuong trinh hoc\n--------------\n" ;
}

void boSungMonHoc(){
    string maHocPhan ; cin >> maHocPhan ;
    slMonHoc ++ ;

    string diem , review ;
    cin >> diem ;
    getline(cin, review) ;

    bool batBuoc ; cin >> batBuoc;

    int id = nameToInt[maHocPhan] ;

    slTinChi += V[id].second.first;
    sum += grade[diem] * 1.0 * V[id].second.first;

    if(diem == "f")
        dem[0] ++ ;
    else {
        int idx = 1 + 2 * int(diem[0] - 'a') + bool(int(diem.size()) > 1);
        dem[idx] ++;
    }

    V[id].first.first = diem ;
    V[id].first.second = V[id].first.second + "\n" + review;
    V[id].second.second = batBuoc;
}

void boSungReview(){
    string maHocPhan , review ;
    getline(cin , maHocPhan);
    getline(cin , maHocPhan);

    getline(cin , review);
  ///  getline(cin , review);
   ///  cout << "? " << review << "\n" ;

    int id = nameToInt[maHocPhan] ;
    V[id].first.second = V[id].first.second + "\n" + review;
}

signed main(){
    if(ifstream("230902.inp")){
        freopen("230902.inp", "r", stdin);
        freopen("230902.out", "w", stdout);
    }

    grade["a+"] = 4.0 , grade["a"] = 3.7 , grade["b+"] = 3.5 , grade["b"] = 3.0 , grade["c+"] = 2.5 , grade["c"] = 2.0 , grade["d+"] = 1.5 , grade["d"] = 1.0, grade["f"] = 0.0;

    /// nhap du lieu
    string maHocPhan, cmt ;
    getline(cin , cmt);
    while(cin >> maHocPhan){
        if(maHocPhan == ".")
            break;

        string tenMonHoc ; cin >> tenMonHoc ;
        int soTinChi ; cin >> soTinChi ;
        bool batBuoc ; cin >> batBuoc ;

        nameToname[maHocPhan] = tenMonHoc ;
        nameToInt[maHocPhan] = slMonHoc ;
        intToName[slMonHoc] = maHocPhan ;
        slMonHoc ++ ;

        V.push_back({ {"Chua hoc", ""}, {soTinChi, batBuoc} });
    }

    slMonHoc = 0 ; /// dem so mon hoc da hoan thanh

    /// nhap mon tien quyet
    getline(cin , cmt); getline(cin , cmt);
    while(cin >> maHocPhan){
        if(maHocPhan == ".")
            break;

        int u = nameToInt[maHocPhan];

        string maHocPhanTienQuyet;
        while(cin >> maHocPhanTienQuyet){
            if(maHocPhanTienQuyet == ".")
                break;

            int v = nameToInt[maHocPhanTienQuyet] ;

            adj[u].push_back(v);
        }
    }

    /// nhap diem + review
    getline(cin , cmt); getline(cin , cmt);
    while(cin >> maHocPhan){
        if(maHocPhan == ".")
            break;

        slMonHoc ++ ;

        string diem , review ;
        cin >> diem ;
        getline(cin, review) ;

        int id = nameToInt[maHocPhan] ;

        slTinChi += V[id].second.first;
        sum += grade[diem] * 1.0 * V[id].second.first;

        if(diem == "f")
            dem[0] ++ ;
        else {
            int idx = 1 + 2 * int(diem[0] - 'a') + bool(int(diem.size()) > 1);
            dem[idx] ++;
        }

        V[id].first.first = diem ;
        V[id].first.second = V[id].first.second + "\n" + review;
    }

    /// nhap yeu cau
    /*
        1 la xem gpa (done)
        2 la xem mon hoc (ten mon hoc + so tin chi + diem + review) (done)
        3 la xem thong ke diem (done)
        4 la them mot mon hoc (nhap ma hoc phan  , nhap diem, review)(done)
        5 la xem neu muon hoc mot mon hoc thi can phai hoc nhung mon hoc nao (tien quyet),
        di kem voi do la xem cac mon do da co diem chua (da hoan thanh chua) (done)
        6 la xem tien do hoc tap (hoan thanh bao nhieu % tin chi quy dinh) (done)
        7 la bo sung review cho mon hoc (review cu + \n + review moi) (done)
    */
    getline(cin , cmt); getline(cin , cmt);

    int option ;
    while(cin >> option){
        switch(option){
            case 0 :{
                 return 0;
                 break;
            }
            case 1 : {
                /// xem gpa
                xemGPA();
                break;
            }
            case 2 : {
                /// xem mon hoc (ten mon hoc + so tin chi + diem + review)
                 getline(cin, maHocPhan);
                getline(cin, maHocPhan);
                xemMonHoc(maHocPhan) ;
                break;
            }
            case 3 : {
                /// xem thong ke diem
                thongKeDiem();
                break;
            }
            case 4 : {
                /// them mot mon hoc (nhap ma hoc phan  , nhap diem, review)
                boSungMonHoc();
                break;
            }
            case 5 : {
                /// xem neu muon hoc mot mon hoc thi can phai hoc nhung mon hoc nao (nhap ma hoc phan)
                getline(cin, maHocPhan);
                getline(cin, maHocPhan);
                timCacMonTienQuyet(maHocPhan);
                break;
            }
            case 6 : {
                /// xem tien do hoc tap (hoan thanh bao nhieu % tin chi quy dinh)
                tienDoHocTap();
                break;
            }
            case 7 : {
                /// bo sung review cho mon hoc (nhap ma mon hoc , review bo sung)
                boSungReview();
                break;
            }
            default : {
                cout << "Yeu cau khong hop le , hay thu lai !\n-------------------\n" ;
                break;
            }
        }
    }

    return 0;
}

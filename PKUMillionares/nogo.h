#ifndef NOGO_H
#define NOGO_H

#include <QMainWindow>
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<string.h>
#include<cstring>
#include<queue>
#include<cmath>
#include<fstream>
#include<Windows.h>
#include<filesystem>
#include<iomanip>
#include <thread>
#include <chrono>
#define ll long long
#define maxn 10000000
using namespace std::literals;
using namespace std;
using namespace std::filesystem;
int a[23][23];
int nandu[2];
int AI_LX[2];
int tmp_air[5];//用于存储xg时所需要的气;
int ttpp[10001];
bool ygz,yhq,hqtp;//已估值为1;
double gz1, gz2;//gz1 倒数估值,gz2 特别估值;
int COUNT;
double MTCSXS;
int shichang;
queue<int>Q;

int xx[4] = { 1,0,-1,0 }, yy[4] = { 0,1,0,-1 };
bool v[23][23], vq[23][23];
string namess[10] = { "Player1","Robot 1","Player2", "Robot 2","Player","Robot" };
int player[2];
int history[600][2], bs, siz, mid, hq[2], djs, MODE, now, zt, nowbs, noww, usv, wz;
int win;
string name;
struct dian {//白棋1;黑棋-1;
    int x, y; double value, gz1, gz2;
    dian(int x, int y, double value, double gz1, double gz2) :x(x), y(y), value(value), gz1(gz1), gz2(gz2) {}
};
struct cmp {
    bool operator()(dian u, dian v) { return u.value < v.value; }
};
struct cjd {
    int x, y, fh;//fh表示刚刚走完的这步棋是什么颜色的
    vector<int>choices_1;//下一步
    vector<int>choices_2;//敌人
    vector<int>choices_3;//both
    vector<int>sons;
    int choice_num1, choice_num2, choice_num3;
    //vector<int>histories;
    //int histories_num;
    double w; int n;
    double GZ;
    double UTB;
    int sons_num;
    int fa;
    int bh;
}CJD[100001];
int CJDCNT;

int dis(int u, int v) {
    return abs(u - mid) + abs(v - mid);
}

void printBoard(int x, int y) {
    if (x == 1) {
        if (y == 1) std::cout << "┌─";
        else if (y == siz) std::cout << "┐";
        else std::cout << "┬─";
    }
    else if (x == siz) {
        if (y == 1) std::cout << "└─";
        else if (y == siz) std::cout << "┘";
        else std::cout << "┴─";
    }
    else {
        if (y == 1) std::cout << "├─";
        else if (y == siz) std::cout << "┤";
        else std::cout << "┼─";
    }
}
void sc() {
    QString NAMETMP1=namess[player[1]].c_str();
    QString NAMETMP2=namess[player[0]].c_str();
    ui->label4_1->setText(NAMETMP1+"VS"+NAMETMP2);
    DD=15;
    X0=360-siz*DD;Y0=360-siz*DD;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QColor(Qt::black));
    for(int i=0;i<siz;++i){painter.drawLine(X0,Y0+2*i*DD,X0+2*(siz-1)*DD,Y0+2*i*DD);painter.drawLine(X0+2*i*DD,Y0,X0+2*i*DD,Y0+2*(siz-1)*DD);}
    for(int i=1;i<=siz;++i)
        for(int j=1;j<=siz;++j){
            if(a[i][j]==-1){painter.setBrush(Qt::black);painter.drawEllipse(X0+(2*i-3)*DD,Y0+(2*j-3)*DD,2*DD,2*DD);}
            else if(a[i][j]==1){painter.setBrush(Qt::white);painter.drawEllipse(X0+(2*i-3)*DD,Y0+(2*j-3)*DD,2*DD,2*DD);}
        }
}

int DFS(int x, int y) {
    int an = 0;
    memset(vq, 0, sizeof(vq));
    v[x][y] = true;
    queue<dian>Q;
    Q.push(dian(x, y, 0, 0, 0));
    while (!Q.empty()) {
        dian tmp = Q.front(); Q.pop();
        for (int i = 0; i < 4; i++) {
            switch (a[tmp.x + xx[i]][tmp.y + yy[i]] * a[tmp.x][tmp.y]) {
            case 1:if (!v[tmp.x + xx[i]][tmp.y + yy[i]])Q.push(dian(tmp.x + xx[i], tmp.y + yy[i], 0, 0, 0)), v[tmp.x + xx[i]][tmp.y + yy[i]] = true; break;
            case 0:if (!vq[tmp.x + xx[i]][tmp.y + yy[i]])an++, vq[tmp.x + xx[i]][tmp.y + yy[i]] = true; break;
            }
        }
    }
    return an * a[x][y];
}
void gz() {
    double an = 0;
    bool special = false;
    gz1 = gz2 = 0;
    memset(v, 0, sizeof(v)); memset(vq, 0, sizeof(vq));
    for (int i = 1; i <= siz; i++) {
        if (special)break;
        for (int j = 1; j <= siz; j++)
            if (a[i][j] != 0 && !v[i][j]) {
                int m = DFS(i, j);//白棋为正黑棋为负;
                if (m == 0) {
                    special = true;
                    break;
                }
                else gz1 += 100 * 1.0 / m;
            }
    }
    if (special)gz1 = maxn;
    ygz = true;
}
double xg(int u, int vv) {
    if (!ygz) {
        gz();
        return gz1;
    }
    memset(v, 0, sizeof(v));
    tmp_air[0] = 0;
    int fh = a[u][vv]; a[u][vv] = 0;
    int ths = 0;  bool special = true;
    for (int i = 0; i < 4; i++) {
        if (fh * a[u + xx[i]][vv + yy[i]] == 1) {//说明同号
            special = false;
            if (v[u + xx[i]][vv + yy[i]])continue;
            else {
                tmp_air[++ths] = DFS(u + xx[i], vv + yy[i]);
            }
        }
        else if (fh * a[u + xx[i]][vv + yy[i]] == -1) {
            if (v[u + xx[i]][vv + yy[i]])continue;
            else {
                int sj = DFS(u + xx[i], vv + yy[i]);
                if (abs(sj) == 1) { special = true; break; }
                else  gz1 -= 100.0 * fh / ((sj + fh) * sj);
            }
        }
        else if (a[u + xx[i]][vv + yy[i]] == 0) { special = false; }
    }
    a[u][vv] = fh;
    if (special) { gz1 = maxn; return maxn; }
    memset(v, 0, sizeof(v));
    int uu = DFS(u, vv);
    if (uu == 0) { gz1 = maxn; return maxn; }
    for (int i = 1; i <= ths; i++) {
        gz1 -= 100.0 / tmp_air[i];
    }
    gz1 += 100.0 / uu;
    return gz1;
}
bool able(int u, int vv, int fh) {
    if (a[u][vv] != 0)return false;
    memset(v, 0, sizeof(v));
    bool special = true;
    for (int i = 0; i < 4; i++) {
        if (fh * a[u + xx[i]][vv + yy[i]] == 1) {//说明同号
            special = false;
        }
        else if (fh * a[u + xx[i]][vv + yy[i]] == -1) {
            if (v[u + xx[i]][vv + yy[i]])continue;
            else {
                int sj = DFS(u + xx[i], vv + yy[i]);
                if (abs(sj) == 1) { special = true; break; }
            }
        }
        else if (a[u + xx[i]][vv + yy[i]] == 0) { special = false; }
    }
    if (special) { return false; }
    memset(v, 0, sizeof(v));
    a[u][vv] = fh;
    int uu = DFS(u, vv);
    a[u][vv] = 0;
    if (uu == 0) { return false; }
    return true;
}
int ALL_able() {
    int ANS=0;
    for(int i=1;i<=siz;i++)
        for (int j = 1; j <= siz; j++) {
            if (!a[i][j]) {
                if (able(i, j, 1))ANS++;
                if (able(i, j, -1))ANS--;
            }
        }
    return ANS;
}
bool ABLE(int u) {
    for(int i=1;i<=siz;i++)
        for (int j = 1; j <= siz; j++) {
            if (!a[i][j]) {
                if (able(i, j, u))return true;
            }
        }
    return false;
}

cjd xj(int u, int v, int z, int father) {
    cjd tmp;
    tmp.x = u; tmp.y = v; tmp.fh = z;
    tmp.choice_num1 = tmp.choice_num2 = tmp.choice_num3 = 0;
    if (father == 0) {
        for (int i = 1; i <= siz; i++)
            for (int j = 1; j <= siz; j++) {
                if (able(i, j, z)) {
                    if (able(i, j,  -1 * z))tmp.choices_3.push_back(10 * i + j), tmp.choice_num3++;
                    else tmp.choices_1.push_back(10 * i + j), tmp.choice_num1++;
                }
                else if (able(i, j, -1 * z))tmp.choices_2.push_back(10 * i + j), tmp.choice_num2++;
            }
    }
    else {
        a[u][v] = z;//father1->son2;father2->son1;
        xg(u, v);
        for (int i = 0; i < CJD[father].choice_num1; i++)
            if (able(CJD[father].choices_1[i] / 10, CJD[father].choices_1[i] % 10, -1 * z))
                tmp.choices_2.push_back(CJD[father].choices_1[i]), tmp.choice_num2++;
        for (int i = 0; i < CJD[father].choice_num2; i++)
            if (able(CJD[father].choices_2[i] / 10, CJD[father].choices_2[i] % 10, z))
                tmp.choices_1.push_back(CJD[father].choices_2[i]), tmp.choice_num1++;
        for (int i = 0; i < CJD[father].choice_num3; i++) {
            if (able(CJD[father].choices_3[i] / 10, CJD[father].choices_3[i] % 10, z)) {
                if (able(CJD[father].choices_3[i] / 10, CJD[father].choices_3[i] % 10, -1 * z))tmp.choices_3.push_back(CJD[father].choices_3[i]), tmp.choice_num3++;
                else tmp.choices_1.push_back(CJD[father].choices_3[i]), tmp.choice_num1++;
            }
            else if (able(CJD[father].choices_3[i] / 10, CJD[father].choices_3[i] % 10, -1 * z))tmp.choices_2.push_back(CJD[father].choices_3[i]), tmp.choice_num2++;
        }
    }
    tmp.fa = father;
    tmp.sons_num = 0; tmp.GZ = gz1;
    tmp.UTB = 0; tmp.w = tmp.n = 0;
    CJD[++CJDCNT] = tmp; CJD[CJDCNT].bh = CJDCNT;
    return CJD[CJDCNT];
}
int EXPAND(cjd &root) {
    gz1 = root.GZ;
    if (root.choice_num2 + root.choice_num3 == 0)return root.bh;

    if (root.choice_num3 > root.sons_num) {
        int tt1 = root.choices_3[root.sons_num] / 10, tt2 = root.choices_3[root.sons_num] % 10;
        root.sons_num++; xj(tt1, tt2, root.fh * -1, root.bh);
        //cout << root.sons.data() << endl;
        root.sons.push_back(CJDCNT);
        return root.sons[root.sons_num - 1];
    }
    else if (root.choice_num3 + root.choice_num2 > root.sons_num) {
        int tt1 = root.choices_2[root.sons_num - root.choice_num3] / 10, tt2 = root.choices_2[root.sons_num - root.choice_num3] % 10;
        root.sons_num++;
        root.sons.push_back(xj(tt1, tt2, root.fh * -1, root.bh).bh);
        return root.sons[root.sons_num - 1];
    }

    double maxUTB = -1000000; int bestson = 0; bool IFFIRST = true;
    for (int i = 0; i < root.sons_num; i++) {
        if (CJD[root.sons[i]].n == 0)CJD[root.sons[i]].UTB = 10000000;
        else CJD[root.sons[i]].UTB = (CJD[root.sons[i]].w / CJD[root.sons[i]].n) + sqrt(MTCSXS * log(COUNT) / CJD[root.sons[i]].n);
        if (CJD[root.sons[i]].UTB > maxUTB)bestson = i, maxUTB = CJD[root.sons[i]].UTB;
    }
    a[CJD[root.sons[bestson]].x][CJD[root.sons[bestson]].y] = CJD[root.sons[bestson]].fh;
    return EXPAND(CJD[root.sons[bestson]]);
}

dian AI2(int fh) {
    if (bs == 1 && fh == -1)return dian(1, 1, 0, 0, 0);
    fill(CJD + 1, CJD + 100000, cjd{});
    CJDCNT = 0;
    COUNT = 0;
    auto start = std::chrono::system_clock::now();
    auto end = std::chrono::system_clock::now();
    cjd Root = xj(0, 0, -1 * fh, 0);
    if (Root.choice_num2 + Root.choice_num3 == 0) {
        return dian(0, 0, 0, 0, 0);
    }
    while ((end - start) / 1ms < shichang) {
        COUNT++;
        int ttmm = EXPAND(Root);
        int VALUE = 100*(CJD[ttmm].choice_num1 - CJD[ttmm].choice_num2) + CJD[ttmm].GZ*CJD[ttmm].fh;
        while (CJD[ttmm].fa != 0) {
            CJD[ttmm].n++; CJD[ttmm].w += VALUE;
            VALUE *= -1;
            a[CJD[ttmm].x][CJD[ttmm].y] = 0,gz1=CJD[CJD[ttmm].fa].GZ;
            ttmm = CJD[ttmm].fa;
        }
        end = std::chrono::system_clock::now();
    }
    printf("第%d步共耗时%dms,拓展%d次,平均用时%lfms,用了%d个CJD\n", bs, (end - start) / 1ms, COUNT, ((end - start) / 1ms) * 1.0 / COUNT,CJDCNT);
    double maxVALUE = -100000;
    int BESTSONS[82];
    BESTSONS[0] = 0;
    for (int i = 0; i < Root.sons_num; i++) {
        if (CJD[Root.sons[i]].n == 0)continue;
        if (maxVALUE < CJD[Root.sons[i]].w*1.0/CJD[Root.sons[i]].n) {
            BESTSONS[0] = 0, BESTSONS[++BESTSONS[0]] = i;
            maxVALUE = CJD[Root.sons[i]].w*1.0/CJD[Root.sons[i]].n;
        }
        else if (maxVALUE == CJD[Root.sons[i]].w * 1.0 / CJD[Root.sons[i]].n) {
            BESTSONS[++BESTSONS[0]] = i;
        }
    }
    int RAND = rand() % BESTSONS[0];
    RAND++;
    dian anan = { CJD[Root.sons[BESTSONS[RAND]]].x,CJD[Root.sons[BESTSONS[RAND]]].y,0,0,0 };
    return anan;
}
int main() {

youxijiemian:
    if (MODE == 4)goto youxijiemian2;
    cd();
    bs++;
    while (bs <= 0)bs++;
    noww = bs % 2;
    if (player[noww] % 2 == 1) {
        usv = lun(noww);
        dian m = { 0,0,0,0,0 };
        if (AI_LX[noww] == 1) {
            m = AI(usv, 1 - 2 * noww);
            while (m.x == 0 && m.y == 0 && usv > 1) {
                usv--, m = AI(usv, 1 - 2 * noww);
            }
        }
        else {
            MTCSXS = XS(noww);
            m = AI2(1 - 2 * noww);
        }
        if (m.x == 0 && m.y == 0 && usv == 1) {
            cout << namess[player[noww]] << "投子认负\n", win = 1 - noww;
            goto jiesuan;
        }
        else {
            a[m.x][m.y] = 1 - 2 * noww;
            xg(m.x, m.y);
            //sc();
            //cout << namess[player[noww]] << "选择下在(" << m.x << ',' << m.y << ')' << endl;
            history[bs][0] = m.x, history[bs][1] = m.y;
            goto youxijiemian;
        }
    }
    cout << "\033[2J" << "\033[H";
    sc();
    if (bs > 1)cout << "上一步,对手选择下在(" << history[bs - 1][0] << ',' << history[bs - 1][1] << ')' << endl;
    if (!ABLE(1-2*noww)) { cout << "您已无处可下，您输了！\n3s后进入悔棋界面\n"; win = 1 - noww;std::this_thread::sleep_for(3s); goto xiaojie;
    }
    cout << "选择你的操作(输入选项前的对应序号):\n" << "1:两个正整数,以空格隔开,表示行和列\n";
    if (bs >= 2)cout << "2:输入200悔棋(你的剩余悔棋次数为:" << hq[noww] << "次 \n";
    if (bs == 1)cout << "(现在是第一步,请注意不要下在棋盘正中间否则你将被判负) \n  ";
    cout << "1000:暂停程序\n";
    while (true) {
        cin >> tmp2;
        if (std::cin.eof() || std::cin.bad()) { std::exit(0); }
        if (std::cin.fail()) {
            cout << "输入不合法，请重新输入 \n"; cin.clear(); cin.ignore(1e9, '\n');
        }
        else break;
    }
    if (tmp2 == 200) {
        if (hq[noww] <= 0) {
            cout << "你没有悔棋次数了！\n3s后自动返回游戏界面\n"; std::this_thread::sleep_for(3s); goto youxijiemian;
        }
        else {
            hqtp = true; win = -1;
        }
        goto xiaojie;
    }
    if (tmp2 == 1000) {
        cout << "\033[2J" << "\033[H";
        cout << "选择你的操作(输入选项前的对应序号):\n" << "1:继续游戏\n";
        cout << "2:悔棋(你的剩余悔棋次数为:" << hq[noww] << "次 \n";
        cout << "3:存档并返回个人界面 \n";
        cout << "4:存档并结束游戏\n";
        while (true) {
            cin >> tmp2;
            if (std::cin.eof() || std::cin.bad()) { std::exit(0); }
            if (std::cin.fail()||(tmp2!=1&&tmp2!=2&&tmp2!=3&&tmp2!=4)) {
                cout << "输入不合法，请重新输入 \n"; cin.clear(); cin.ignore(1e9, '\n');
            }
            else break;
        }
        if (tmp2 == 1)goto youxijiemian;
        else if (tmp2 == 2)goto xiaojie;
        else if (tmp2 == 3) { cd(); goto erjijiemian; }
        else { cd(); return 0; }
    }
    while (true) {
        cin >> tmp3;
        if (std::cin.eof() || std::cin.bad()) { std::exit(0); }
        if (std::cin.fail()) {
            cout << "输入不合法，请重新输入 \n"; cin.clear(); cin.ignore(1e9, '\n');
        }
        else break;
    }
    if (tmp2<0 || tmp2>siz || tmp3<0 || tmp3>siz) {
        cout << "你把棋子下在了棋盘之外!\n3s后自动重置，请您重新输入\n"; bs--; std::this_thread::sleep_for(3s); goto youxijiemian;
    }
    if (a[tmp2][tmp3] != 0) {
        cout << "你把棋子下在了原来就有的地方!\n3s后自动重置，请您重新输入\n"; bs--; std::this_thread::sleep_for(3s); goto youxijiemian;
    }
    if (bs == 1 && tmp2 == mid && tmp3 == mid) {
        //a[tmp2][tmp3] = 1 - 2 * noww;
        //history[bs][0] = tmp2, history[bs][1] = tmp3;
        cout << namess[player[noww]] << "选择下在(" << tmp2 << ',' << tmp3 << ')' << endl;
        cout << "你第一步下在了棋盘正中央!\n3s后自动重置，请您重新输入\n"; bs--; std::this_thread::sleep_for(3s); goto youxijiemian;
    }
    else {
        a[tmp2][tmp3] = 1 - 2 * noww;
        history[bs][0] = tmp2, history[bs][1] = tmp3;
        cout << namess[player[noww]] << "选择下在(" << tmp2 << ',' << tmp3 << ')' << endl;
        if (abs(xg(tmp2, tmp3)) > maxn / 100) {
            cout << "有一方的子被提出了棋盘!\n你输了!\n3s后自动进入悔棋界面\n"; win = 1 - noww; std::this_thread::sleep_for(3s); goto xiaojie;
        }
        goto youxijiemian;
    }
xiaojie:
    ygz = false;
    yhq = false;
    if (hq[noww] < 1) {
        cout << "你没有悔棋次数了！\n3s后自动进入结算界面\n"; std::this_thread::sleep_for(3s);  goto jiesuan; }
    else {
        nowbs = bs;
        tmp4 = 1;
        while (tmp4 != 2) {
            if (bs == 0 || (bs == 1 && nowbs % 2 == 0))goto youxijiemian;
            cout << "\033[2J" << "\033[H";
            sc();
            if (yhq) {
                cout << "已经完成了悔棋\n你的剩余悔棋次数为:" << hq[noww] << "次 ,是否继续悔棋？\n";
                cout << "1: 悔棋\n2: 不悔棋\n";
            }
            else {
                cout << "你的剩余悔棋次数为:" << hq[noww] << "次 ,是否悔棋？\n";
                cout << "1: 悔棋\n2: 不悔棋\n";
            }
            while (true) {
                cin >> tmp4;
                if (std::cin.eof() || std::cin.bad()) { std::exit(0); }
                if (std::cin.fail() || (tmp4 != 1 && tmp4 != 2)) {
                    cout << "输入不合法，请重新输入 \n"; cin.clear(); cin.ignore(1e9, '\n');
                }
                else break;
            }
            if (tmp4 == 1) {
                if (hq[noww] <= 0) {
                    cout << "你不能悔棋了\n3s后自动返回游戏界面\n"; std::this_thread::sleep_for(3s); goto youxijiemian;
                }
                win = -1;
                hq[noww]--;
                ygz = false; yhq = true;
                if (hqtp) {
                    bs--; hqtp = false; a[history[bs][0]][history[bs][1]] = 0; bs--; a[history[bs][0]][history[bs][1]] = 0; bs--;
                }
                else {
                    if ((nowbs - bs) % 2 == 0) {
                        a[history[bs][0]][history[bs][1]] = 0; bs--;
                    }
                    else {
                        a[history[bs][0]][history[bs][1]] = 0; bs--; a[history[bs][0]][history[bs][1]] = 0; bs--;
                    }
                }
            }
        }
        if (win!=-1)goto jiesuan;
        else goto youxijiemian;
    }

youxijiemian2:
    bs++;
    while (bs <= 0)bs++;
    noww = bs % 2;
    sc();
    if (player[noww] % 2 == 1) {
        auto start = std::chrono::system_clock::now();
        usv = lun(noww);
        dian m = { 0,0,0,0,0 };
        if (AI_LX[noww] == 1) {
            m = AI(usv, 1 - 2 * noww);
            while (m.x == 0 && m.y == 0 && usv > 1) {
                usv--, m = AI(usv, 1 - 2 * noww);
            }
        }
        else {
            MTCSXS = XS(noww);
            m = AI2(1 - 2 * noww);
        }
        auto end = std::chrono::system_clock::now();
        printf("第%d步共耗时%dms\n", bs, (end - start) / 1ms);
        if (m.x == 0 && m.y == 0) {
            cout << namess[player[noww]] << "投子认负\n", win = 1 - noww;
            goto jiesuan;
        }
        else {
            a[m.x][m.y] = 1 - 2 * noww;
            xg(m.x, m.y);
            cout << "\033[2J" << "\033[H";
            sc();
            cout << namess[player[noww]] << "选择下在(" << m.x << ',' << m.y << ')' << endl;
            history[bs][0] = m.x, history[bs][1] = m.y;
            cd();
            //std::this_thread::sleep_for(1s);
            goto youxijiemian2;
        }
    }


jiesuan:
    cout << namess[player[win]] << "获胜!";
    cout << "赢了" << ALL_able() * (1 - 2 * win)<<"个点" << endl;
    zt = 1; cd();
    cout << "选择你的操作:\n  1:返回上一级\n  2:复盘本局 \n  3:结束程序\n";
    while (true) {
        cin >> tm;
        if (std::cin.eof() || std::cin.bad()) { std::exit(0); }
        if (std::cin.fail() || (tm != 1 && tm != 2 && tm != 3)) {
            cout << "输入不合法，请重新输入 \n"; cin.clear(); cin.ignore(1e9, '\n');
        }
        else break;
    }
    if (tm == 1)goto erjijiemian;
    if (tm == 2) { cd(); goto fupanjiemian; }
    if (tm == 3) { cd(); return 0; }

fupanjiemian:
    dq(1); noww = 1; gz1 = gz2 = 0; ygz = -1;
    for (int i = 1; i <= bs; i++) {
        noww *= -1;
        a[history[i][0]][history[i][1]] = noww;
        //xg(history[i][0], history[i][1]);
        sc();
        cout << namess[player[(1 - noww) / 2]] << "选择下在(" << history[i][0] << ',' << history[i][1] << ')' << endl;
        //cout << "gz1=" << gz1 << "  gz2=" << gz2 << endl;
        cout << "选择你的操作\n  1:下一步\n  2:返回上一级(用户界面)\n  3:结束程序\n";
        while (true) {
            cin >> tm;
            if (std::cin.eof() || std::cin.bad()) { std::exit(0); }
            if (std::cin.fail() || (tm != 1 && tm != 2 && tm != 3)) {
                cout << "输入不合法，请重新输入 \n"; cin.clear(); cin.ignore(1e9, '\n');
            }
            else break;
        }
        if (tm == 1)continue;
        if (tm == 2)goto erjijiemian;
        if (tm == 3)return 0;
    }
    cout << "选择你的操作\n  1:再看一遍\n  2:返回上一级\n  3:结束程序\n";
    while (true) {
        cin >> tm;
        if (std::cin.eof() || std::cin.bad()) { std::exit(0); }
        if (std::cin.fail() || (tm != 1 && tm != 2 && tm != 3)) {
            cout << "输入不合法，请重新输入 \n"; cin.clear(); cin.ignore(1e9, '\n');
        }
        else break;
    }
    if (tm == 1)goto fupanjiemian;
    if (tm == 2)goto erjijiemian;
    if (tm == 3)return 0;
    return 0;
}
namespace Ui {
class Nogo;
}

class Nogo : public QMainWindow
{
    Q_OBJECT

public:
    explicit Nogo(QWidget *parent = nullptr);
    ~Nogo();
    void sc();
private:
    Ui::Nogo *ui;
};

#endif // NOGO_H

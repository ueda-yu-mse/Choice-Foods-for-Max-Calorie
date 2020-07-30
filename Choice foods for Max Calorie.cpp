#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
#include<string>
#include<cassert>
#include<mutex>

using namespace std;

struct Item //クラス（Item）の定義
{
    string name; //食べ物の名前
    int calorie; //食べ物のカロリー
    int value; //食べ物の値段
};

vector<Item> foods{ 5 }; //食べ物を格納するためのコンテナ

void Cin() //入力用の関数
{
    cout << "～ 5種類の食べ物から、1000円以内で最大限のカロリーを摂取するための選定プログラム ～\n" << endl;

    cout << "1つ目の食べ物の名前を入力してください："; cin >> foods[0].name;
    cout << "カロリーを入力してください[kcal]:"; cin >> foods[0].calorie;
    assert(foods[0].calorie > 0);                                                  //valueやcalorieに整数ではなく、文字列を打ち込んだ時にもエラーが発生する
    cout << "値段を入力してください[円]:"; cin >> foods[0].value;
    assert(foods[0].value > 0);

    cout << "2つ目の食べ物の名前を入力してください："; cin >> foods[1].name;
    cout << "カロリーを入力してください[kcal]:"; cin >> foods[1].calorie;
    assert(foods[1].calorie > 0);
    cout << "値段を入力してください[円]:"; cin >> foods[1].value;
    assert(foods[1].value > 0);

    cout << "3つ目の食べ物の名前を入力してください："; cin >> foods[2].name;
    cout << "カロリーを入力してください[kcal]:"; cin >> foods[2].calorie;
    assert(foods[2].calorie > 0);
    cout << "値段を入力してください[円]:"; cin >> foods[2].value;
    assert(foods[2].value > 0);

    cout << "4つ目の食べ物の名前を入力してください："; cin >> foods[3].name;
    cout << "カロリーを入力してください[kcal]:"; cin >> foods[3].calorie;
    assert(foods[3].calorie > 0);
    cout << "値段を入力してください[円]:"; cin >> foods[3].value;
    assert(foods[3].value > 0);

    cout << "5つ目の食べ物の名前を入力してください："; cin >> foods[4].name;
    cout << "カロリーを入力してください[kcal]:"; cin >> foods[4].calorie;
    assert(foods[4].calorie > 0);
    cout << "値段を入力してください[円]:"; cin >> foods[4].value;
    assert(foods[4].value > 0);

    cout << endl;
}

int totalcalorie = 0; //総カロリーの初期値
int maxvalue = 1000; //所持金は1000円

void Depthfirstserch(int calorie, int value, int i) //深さ優先探索を用いてナップサック問題を解く
{
    if (value > maxvalue) //再帰の終了条件
        return;
    totalcalorie = max({ totalcalorie,calorie }); //総カロリーを更新する
    if (foods.size() <= i) //再帰の終了条件
        return;
    Item item{ foods[i] }; 
    Depthfirstserch(calorie + item.calorie, value + item.value, i + 1); //食べ物を取る場合
    Depthfirstserch(calorie, value, i + 1); //食べ物を取らない場合
}

void CoutName() //食べ物の名前を出力する
{
    vector<string> vec{ foods[0].name, foods[1].name, foods[2].name, foods[3].name, foods[4].name };
    for (auto j = vec.begin(); j != vec.end(); ++j) //イテレータの利用
        cout << *j << ", ";
}

int Sumvalue = 0; //使った金額

void doSomething()
{
    throw runtime_error("総カロリーを得るための組み合わせが複数個見つかりました。申し訳ございませんが、食べ物を変更してもう一度お試しください。");
}

void Choicefood() //どの食べ物を選んだのか判断する
{

    int a, b, c, d, e, f;

    for (a = 0; a < 2; ++a)
    {
        for (b = 0; b < 2; ++b)
        {
            for (c = 0; c < 2; ++c)
            {
                for (d = 0; d < 2; ++d)
                {
                    for (e = 0; e < 2; ++e)
                    {
                        f = foods[0].calorie * a + foods[1].calorie * b + foods[2].calorie * c + foods[3].calorie * d + foods[4].calorie * e;
                            if (f == totalcalorie)
                            {
                                try //組み合わせが複数見つかった場合の処理
                                {
                                    if(Sumvalue > 1000)
                                        doSomething();
                                }
                                catch (exception& e)
                                {
                                    cout << endl;
                                    cerr << e.what() << endl;
                                    assert(Sumvalue <= 1000);
                                };
                                    if (a) { cout << foods[0].name << "( " << foods[0].value << "円 ) ,"; Sumvalue += foods[0].value; } //bool値としてif文を利用
                                    if (b) { cout << foods[1].name << "( " << foods[1].value << "円 ) ,"; Sumvalue += foods[1].value; }
                                    if (c) { cout << foods[2].name << "( " << foods[2].value << "円 ) ,"; Sumvalue += foods[2].value; }
                                    if (d) { cout << foods[3].name << "( " << foods[3].value << "円 ) ,"; Sumvalue += foods[3].value; }
                                    if (e) { cout << foods[4].name << "( " << foods[4].value << "円 ) ,"; Sumvalue += foods[4].value; }       
                            }
                    }
                }
            }
        }
    }
}


int main()
{
    Cin();                                                          //入力
    Depthfirstserch(0, 0, 0);                                      //カロリー摂取量の探索
    CoutName();                                                   //食べ物の名前を出力する
    cout << "の中からお菓子を選ぶ。\n";
    Choicefood();  //どの食べ物を選んだか確認
    cout << "を選んだ時、合計価格は" << Sumvalue << "円となり、最大" << totalcalorie << "kcal を得ることができる。" << endl;
}
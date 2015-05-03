#include <stdio.h>
#include <math.h>

/* 関数のデータを求めるプログラム例 */

#define max 100 // Max number to loop

int main()
{
  int i,n,m;
  double x,y[max];
  
  n=0;
  
  FILE *function;
  function=fopen("function.data","w");

  //のこぎり波の一周期分の数値をつくる。
  for(x=-1.0;x<=1.0;x+=0.1) {
    y[n]=x;
    n++;
  }

  //のこぎり波の生成
  for(i=0;i<max;i++) {
    for(m=0;m<n;m++) {
      fprintf(function,"%f\n",y[m]);
    }
  }

  fclose(function);

  return 0;
}

/* フーリエ変換してスペクトルの強さを求めるプログラム例 */

#define max 10000                       //Nの限界値
#define pi 3.1415926535         //円周率

int dft()
{
  int k,n,N;
  double f[max+1],ReF/*実数部*/,ImF/*虚数部*/;

  FILE *function;
  FILE *fourier;

  //フーリエ変換したいデータをあらかじめファイル function.data に保存しておく
  function=fopen("function.data","r");
  fourier=fopen("fourier.data","w");

  //データの読み込み（ただし実数の成分のみ）
  for(N=0;N<max;N++) {
    if(fscanf(function,"%lf",&f[N]) == EOF) {
      N--;
      break;
    }
  }

  //実数部分と虚数部分に分けてフーリエ変換
  for(n=0;n<N;n++) {
    ReF=ImF=0.0;
    for(k=0;k<N;k++) {
      ReF +=  f[k] * cos(2*pi*k*n/N); // 実数部分cosの計算
      ImF += -f[k] * sin(2*pi*k*n/N); // 虚数部分sinの計算
    }
    fprintf(fourier,"%d %f %f %f\n",n,ReF,ImF,ReF*ReF+ImF*ImF); //最後はスペクトルの強さ
  }

  fclose(function);
  fclose(fourier);
 
  double result[3] = [ReF, ImF, ReF*ReF+ImF*ImF];
  return 0;
}

#define PI 3.1415926535         //円周率

// TODO: メインで作ってるやつ
double dft(int *a /*[入力] 実数数値列としての信号: 配列)*/ ){
  // 配列の要素数を格納
  const int N = sizeof a / sizeof a[0];
  for( int k=0; k<N; ++k ) {
    double Re_sum = 0;
    double Im_sum = 0;
    for( int n=0; n<N; ++n ) {
        double tht = 2*PI*k*n/N;
        Re_sum += a[n] *cos( tht );
        Im_sum += a[n] *sin( tht );
    }// i
    // todo: こっから05-03
    Re->push_back( Re_sum );
    Im->push_back( Im_sum );
  }// j
  return;
}

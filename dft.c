#include <stdio.h>
#include <math.h>

#define DATASIZE 100000
#define PI 3.1415926535 // 円周率
#define DELTA 0.00002   // サンプリング周期

// フーリエ変換
int dft(int *data /*[入力] 実数数値列としての信号: 配列)*/ ){
  // 配列の要素数を格納
  const int N = sizeof data /sizeof data[0];
  double result[N];
  for(int k=0; k <= N/2-1; ++k) {
    double Re = 0;
    double Im = 0;
    for(int n=0; n<N; ++n) {
        double tht = 2*PI*k*n/N;
        Re += data[n] * cos(tht);
        Im += data[n] * sin(tht);
    }// i
    Re = pow(Re, 2.0);
    Im = pow(Im, 2.0);
    double delta;
    delta = pow(DELTA, 2.0);
    result[k] = delta*(Re+Im);
  }// j
  return *result;
}


int main(int argc, char *argv[])
{
  FILE *fp;
  char *filename = argv[1];
  char readline[DATASIZE] = {'\0'};

  /* ファイルのオープン */
  if ((fp = fopen(filename, "r")) == NULL) {
    fprintf(stderr, "%sのオープンに失敗しました.\n", filename);
  }

  int i=0;
  double data[DATASIZE];
  /* ファイルの終端まで文字を読み取り表示する */
  // while ( fgets(readline, DATASIZE, fp) != NULL ) {
  while( fscanf(fp,"%lf",&data[i]) != EOF ){
    printf("%f\n", data[i]);
    i++;
  }

  /* ファイルのクローズ */
  fclose(fp);

  return 0;
}

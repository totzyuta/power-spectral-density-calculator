# Cでパワースペクトル密度を求めるプログラムを作成する

ちょっと諸事情により、C言語で音声データのパワースペクトル密度を求めないといけなくなってしまったのでそのメモ書き（どんな事情

## パワースペクトル密度とは

まず、パワースペクトル密度とはなんでしょうか（全くわかりません）

一応[Wikiのパワースペクトル密度のページ](http://ja.wikipedia.org/wiki/%E3%82%B9%E3%83%9A%E3%82%AF%E3%83%88%E3%83%AB%E5%AF%86%E5%BA%A6)も読みましたが、何を言ってるんだこいつは状態でした。

これについて知るには、まず**パワースペクトル**がなんなのかについて一度まとめておきます。

http://www.tagen.tohoku.ac.jp/labo/ishijima/FFT-02.html


フーリエ変換もパワースクペクトルも、グラフに表すと横軸は周波数になるみたいです。そして縦軸の値が異なる。

フーリエ変換は縦軸を**波形の周波数成分を振幅として表したもの**、パワースペクトルは縦軸を**波形の周波数成分をエネルギーとして表したもの**とのことです。

そして単位は以下のようになります。


> フーリエ変換：[m]
パワースペクトル：エネルギー：[m2/Hz]，もしくはその平方根

そしてパワースペクトル密度とはパワースペクトルとほぼ同義で使われているようです。

強いて言うなら、言葉の意味的に以下のような違いな気がします。

- パワースペクトル: ある一点の周波数のときのエネルギー
- パワースペクトル密度: ある周波数の区間におけるエネルギーの密度

うーん、なんか、曖昧ですが...笑

まぁやってみないことにはわからない、とりあえずコードを書いてみます。



## Cでパワースペクトル密度を求める

### パワースペクトル密度を求めるプログラム

音声データからパワースペクトル密度P(f_k)をC言語のプログラムにより計算し、そのグラフを描きなさい。ただしk=0, 1, ..., N/2-1 に対し、横軸にf_k = k/NΔ [Hz], 縦軸に10log_10_P(f_k) [dB] をプロットする。



（離散）フーリエ変換については以下のブログがすごくよく書かれてて楽しい。ただしC++なので`auto&`や`const auto&`は[使えない](http://d.hatena.ne.jp/prettysoft/20101113/1418577983)か。

http://d.hatena.ne.jp/nurs/20130308/1362762361

- プログラムの世界でできるのは**離散フーリエ変換のみ** (微積分みたいな近似的なことができないから？）

また以下のプログラムも直感的でわかりやすいと思う。

http://www.geocities.jp/supermisosan/spectrum.html




---


そして最終的に高速フーリエ変換でやりたいと考えてたので、同じブログの以下の記事も参考に。

http://d.hatena.ne.jp/nurs/20130617/1371483633

うむ、高速フーリエ変換の式の導出に関しては1mmも理解できるとは思えないけど...笑

プログラムとしてもすごく長いみたいだけど、sinとcosがなくても計算できる+再帰だから速いのかな。

---

ソースコードは以下のようになった。フーリエ変換で求めた数値を、`spectram.dat`というファイルに書き込む設定になっている。

https://github.com/totzYuta/power-spectral-density-calculator/blob/master/dft.c


また、[今回の形式の音声データ](https://github.com/totzYuta/power-spectral-density-calculator/blob/master/data.csv)をパースして正規化するスクリプトもRubyで実装した。

https://github.com/totzYuta/power-spectral-density-calculator/blob/master/normalize.rb


## グラフに描写

これをグラフに描写していく


### gnuplotのインストール

まず、以下を参考にMacでgnuplotを使えるようにしておく。

http://qiita.com/noanoa07/items/a20dccff0902947d3e0c



AquaTermが必要なのでダウンロードして、インストールしておく。　

http://sourceforge.net/projects/aquaterm/?source=typ_redirect


さきほどダウンロードしたaquatermを指定してbrewでgnuplotをインストール。

```
$ brew install gnuplot --with-aquaterm
```



### グラフを描写

以下でgnuplotを対話的に操作できる。

```
$ gnulot
```

まず最初のグラフは

```
gnuplot> set xlabel '[Hz]'
gnuplot> set ylabel '[dB]'
gnuplot> plot 'spectrum.dat' with lines
```

のようにすると、[spectrum1.pdf](https://github.com/totzYuta/power-spectral-density-calculator/blob/master/spectrum1.pdf)のようなグラフを得ることができた。


また、

```
gnuplot> set xlabel '[s]'
gnuplot> set ylabel '[V]'
gnuplot> plot 'voice-data.csv' with lines
```

ようにして自分の音声データをグラフとして描写したところ、[voice-graph.pdf](https://github.com/totzYuta/power-spectral-density-calculator/blob/master/voice-graph.pdf)となった。




また、最初に作成した`spectrum.dat`よりピーク時の周波数を`100`として、２番目に作成した自分の音声データと、周波数100の正弦波のグラフを重ねて表示させてみる。コマンドは以下のように行う。

```
gnuplot> set xlabel '[Hz]'
gnuplot> set ylabel '[dB]'
gnuplot> plot "data-voice.csv" with lines, 0.01*sin(2*3.14*100*x-8.5) with lines
```

結果は[data-voice.pdf](https://github.com/totzYuta/power-spectral-density-calculator/blob/master/voice-sin.pdf)のようになった。

ピーク時の周波数を自分の音声の測定データから読み取ることはむずかしく、目測で100Hzとしたところ大きな波の動きは似た傾向を示しているように見えるグラフとなった。

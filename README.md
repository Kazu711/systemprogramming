# systemprogramming
授業で作成したコードを掲載しています。

## OpenMP.c
OpenMPを利用して、<img src="https://latex.codecogs.com/svg.image?f(x)=&space;-(x-1)^{2}&space;&plus;&space;1&space;"> とx軸で囲まれた領域の面積を求めるプログラムである。この時積分を用いて面積を求めるのではなく、xの範囲(1~2)を1,000,000,000 個に分割してf(x)と分割したxの大きさとの掛け算の結果の合計値を求めることで面積を求める。(矩形積分)

## client-server.c
TCP/IPアプリケーションのモデルの実装として、C言語にてソケットインターフェースを利用したクライアント・サーバモデルの構築を行なった。
サーバ側はこのコードを実行したものを、クライアント側はncatを使用して接続を行う。
クライアント側は[longかdouble　数値]を送り、サーバ側はその受け取った値を10倍にしてクライアント側に表示する。


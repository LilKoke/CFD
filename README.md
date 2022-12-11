# CFD
空気力学第二期末レポートソースコード
## コードの実行方法
### CFD
```
mkdir build
cd build
cmake -S ..
make
```
これでバイナリファイルが```build```内にできる。作成されるバイナリは
5つの条件に合わせて```exp1```から```exp5```まである。
```
./exp1
```
のようにすれば計算が始まる。

### 可視化
可視化にはpythonを用いる
```
python -m venv venv
```
で仮想環境を作成し、
```
pip install numpy　pandas matplotlib
```
を実行。
このままだとJupyter Notebook内で仮想環境が使えないので、
```
pip install ipykernel
ipython kernel install --user --name=mycfd
```
VSCodeを使用している場合、これを実行したのち再起動すると、
Jupyter Notebookを開いたときに左上から作成したkernelを
選択できる。
その後、用意されたJupyter Notebookを実行すればよい。
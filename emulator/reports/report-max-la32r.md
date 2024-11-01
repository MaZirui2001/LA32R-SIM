# 处理器运行报告
## 程序运行情况
|程序名|总指令数|总时钟数|IPC|
|---|---|---|---|
|max-la32r|879|1367|0.643014|

## 分支预测（含预译码纠正）
### 整体情况
|总分支数|总预测正确数|总预测正确率|
|---|---|---|
|332|296|89.1566%|

### 各类指令预测
|分支类型|总分支数|总预测正确数|总预测正确率|
|---|---|---|---|
|**Branch**| 201 | 167 | 83.0846%|
|**JIRL**| 65 | 63 | 96.9231%|
|**BL**| 66 | 66 | 100%|

### 高速缓存命中
|高速缓存|访问次数|命中次数|命中率|
|---|---|---|---|
|**指令高速缓存**| 1113 | 1108 | 99.5508%|
|**数据高速缓存**| 317 | 310 | 97.7918%|
## 流水线阻塞
|阻塞原因|阻塞时钟数|阻塞率|
|---|---|---|
|**指令高速缓存缺失**| 189 | 13.8259%|
|**数据高速缓存缺失**| 171 | 12.5091%|
|**取指队列满**| 50 | 3.65764%|
|**重命名空闲列表空**|0 | 0%|
|**重排序缓冲区满**|14 | 1.02414%|
|**第一算数发射队列满**|0 | 0%|
|**第二算数发射队列满**|53 | 3.8771%|
|**乘除法发射队列满**|0 | 0%|
|**内存读写发射队列满**|23 | 1.68252%|
|**除法器运算**|0 | 0%|
|**写缓冲满**|41 | 2.99927%|

## 发射阶段
### 多发射率
|总发射数|发射率|单发射率|双发射率|三发射率|四发射率|
|---|---|---|---|---|---|---|
|836|61.1558%|47.7273%|37.201%|15.0718%|0%|

### 各发射队列发射率
|发射队列名称|发射率|
|---|---|
|**第一算数发射队列**|29.0417%|
|**第二算数发射队列**|46.7447%|
|**乘除法发射队列**|0.585223%|
|**内存读写发射队列**|25.9693%|

## 提交阶段
|总提交数|提交率|1条提交率|2条提交率|3条提交率|4条提交率|
|---|---|---|---|---|---|
|599|43.8186%|53.2554%|46.7446%|0%|0%|

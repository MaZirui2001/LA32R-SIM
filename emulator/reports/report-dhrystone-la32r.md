# 处理器运行报告
## 程序运行情况
|程序名|总指令数|总时钟数|IPC|
|---|---|---|---|
|dhrystone-la32r|11372245|10177159|1.11743|

## 分支预测（含预译码纠正）
### 整体情况
|总分支数|总预测正确数|总预测正确率|
|---|---|---|
|3243686|3143457|96.91%|

### 各类指令预测
|分支类型|总分支数|总预测正确数|总预测正确率|
|---|---|---|---|
|**Branch**| 3123125 | 3042920 | 97.4319%|
|**JIRL**| 60280 | 40256 | 66.7817%|
|**BL**| 60281 | 60281 | 100%|

### 高速缓存命中
|高速缓存|访问次数|命中次数|命中率|
|---|---|---|---|
|**指令高速缓存**| 8231538 | 8231450 | 99.9989%|
|**数据高速缓存**| 3623431 | 3623395 | 99.999%|
## 流水线阻塞
|阻塞原因|阻塞时钟数|阻塞率|
|---|---|---|
|**指令高速缓存缺失**| 1974 | 0.0193964%|
|**数据高速缓存缺失**| 2841 | 0.0279155%|
|**取指队列满**| 1943662 | 19.0983%|
|**重命名空闲列表空**|0 | 0%|
|**重排序缓冲区满**|1603478 | 15.7557%|
|**第一算数发射队列满**|19997 | 0.196489%|
|**第二算数发射队列满**|100219 | 0.984744%|
|**乘除法发射队列满**|41 | 0.000402863%|
|**内存读写发射队列满**|1141671 | 11.218%|
|**除法器运算**|100272 | 0.985265%|
|**写缓冲满**|380362 | 3.73741%|

## 发射阶段
### 多发射率
|总发射数|发射率|单发射率|双发射率|三发射率|四发射率|
|---|---|---|---|---|---|---|
|7889411|77.5208%|43.4114%|54.0461%|2.54238%|8.87265e-05%|

### 各发射队列发射率
|发射队列名称|发射率|
|---|---|
|**第一算数发射队列**|46.6287%|
|**第二算数发射队列**|39.3526%|
|**乘除法发射队列**|0.590135%|
|**内存读写发射队列**|36.7883%|

## 提交阶段
|总提交数|提交率|1条提交率|2条提交率|3条提交率|4条提交率|
|---|---|---|---|---|---|
|7268297|71.4177%|43.5363%|56.4637%|0%|0%|

# 1. 原生AJAX

## 1.1 AJAX简介

- AJAX全称为Asynchronous JavaScript And XML，**就是异步的Js和 XML**。
- 通过AJAX可以在浏览器中向服务器发送异步请求，最大的优势:**无刷新获取数据**。
- AJAX不是新的编程语言，而是一种将现有的标准组合在一起使用的新方式。

## 1.2 XML简介

- XML可扩展标记语言。

- XML被设计用来传输和存储数据。

- XML和 HTML类似，不同的是HTML中都是预定义标签，而XML中没有预定义标签，全都是自定义标签，用来表示一些数据。

- 比如我有一个学生的数据： name="陆家贤";age=18;gender="男"

  ```xml
  <student>
  	<name>陆家贤</name>
  	<age>18</age>
  	<gender>男</gender>
  </student>
  ```

  后来因为麻烦被json取代

## 1.3 JSON简介

- JSON(JavaScript Object Notation,JS对象标记)是一种轻量级的数据交换格式，目前使用特别广泛。
- 采用完全独立于编程语言的**文本格式**来存储和表示数据。
- 简洁和清晰的层次结构使得JSON成为理想的数据交换语言。
- 易于人阅读和编写，同时也易于机器解析和生成，并有效地提升网络传输效率。

在JavaScript语言中，一切都是对象。因此，任何JavaScript支持的类型都可以通过JSON来表示，例如字符串、数字、对象、数组等。看看他的要求和语法格式:

- 对象表示为键值对，数据由逗号分隔
- 花括号保存对象
- 方括号保存数组

**JSON键值对**是用来保存JavaScript对象的一种方式，和JavaScript对象的写法也大同小异，键/值对组合中的键名写在前面并用双引号`""`包裹，使用冒号`:`分隔，然后紧接着值

```html
    <script type="text/javascript">
    // 编写一个javaScript对象
    var user={
        name : "陆家贤",
        age: 3,
        sex: "sex"}
        
    console.log(user)
    </script>
```

![在这里插入图片描述](https://img-blog.csdnimg.cn/af82c38bef054b7ca2c496952ed2e410.png)

>可展开的对象



JSON,是JavaScript 对象的字符串表示法，它使用文本表示一个JS对象的信息，**本质是一个字符串**。

```html
    <script type="text/javascript">
    //将js对象对象转换成json对象
    var user={
      name : "陆家贤",
      age: 3,
      sex: "sex"}
    //将js对象对象转换成json对象    
    var json = JSON.stringify(user);
    
	console.log(json);
	
    </script>
```

![在这里插入图片描述](https://img-blog.csdnimg.cn/bb63c7ad52a7410db6d8cab1bdb98c40.png)

>不可展开的字符串

**1. 将js对象对象转换成json对象**  

```html
    <script type="text/javascript">
    //将js对象对象转换成json对象
    var user={
      name : "陆家贤",
      age: 3,
      sex: "sex"}
    //将js对象对象转换成json对象    
    var json = JSON.stringify(user);
    
	console.log(json);
	
    </script>
```

![在这里插入图片描述](https://img-blog.csdnimg.cn/bb63c7ad52a7410db6d8cab1bdb98c40.png)

```html
    <script type="text/javascript">
    //将js对象对象转换成json对象
    var user={
      name : "陆家贤",
      age: 3,
      sex: "sex"}
    //将js对象对象转换成json对象    
    var json = JSON.stringify(user);
   	//将JSON对象转换为JavaScript对象
    var obj = JSON.parse(json);
    console.log(obj);
	
    </script>
```

![在这里插入图片描述](https://img-blog.csdnimg.cn/6fce78191269495ca231d358ee3b46d9.png)

## 1.3 AJAX的特点

### 1.3.1 AJAX的优点

1. 可以无需刷新页面而与服务器端进行通信。

2. 允许你根据用户事件来更新部分页面内容。

### 1.3.2 AJAX的缺点

1. 没有浏览历史，不能回退

2. 存在跨域问题(同源)

3. SEO不友好（通过AJAX异步请求结果无法爬虫）

## 1.4 AJAX的使用

### 1.4.1 核心对象

# 2.HTTP

## 2.1 HTTP简介

**超文本传输协议**（Hyper Text Transfer Protocol，HTTP）是一个简单的请求-响应协议，它通常运行在TCP之上。它指定了客户端可能发送给服务器什么样的消息以及得到什么样的响应。请求和响应消息的头以ASCII形式给出；而消息内容则具有一个类似MIME的格式。

## 2.2 HTTP作用

是约定和规定

比如两个人的交流，要是一个人讲中文，一个人讲日文，就无法正常交流

### 2.2.1 请求报文

- 请求行

  请求方式，Url端口，HTTP协议

- 请求头

  Host，Cookie，Content-type（请求体类型）,User-Agent

- 请求空行

- 请求体

  GET请求请求体是空的，POST可以不为空

### 2.2.2 响应报文

- 响应行

  HTTP协议，状态码，状态字符串

- 响应头

  Content-type（响应体类型）,Content-length（响应体长度），Content-encoding（响应体编码方式）

- 响应空行

- 响应体

  主要返回结果

  ```jsp
  <html>
      <head>
          <body>
              <h1>ceit</h1>
          </body>
      </head>
  </html>
  ```

# 3.学习AJAX

- Ajax 不是一种新的编程语言，而是一种用于创建更好更快以及交互性更强的Web应用程序的技术。

- 用来增加B/S的体验性，B/S是未来的主流，并且爆炸性增长，即浏览器和服务器交互
- 产业链：H5+网页+客户端+手机端(Android、IOS)+小程序

利用AJAX可以做:

1. 注册时，输入用户名自动检测用户是否已经存在。

2. 登陆时，提示用户名密码错误
3. 删除数据行时，将行ID发送到后台，后台在数据库中删除，数据库删除成功后，在页面DOM中将数据行也删除。

## 3.1 三步曲

1.编写对应处理的Controller，返回消息或者字符串或者json格式的数据;

⒉.编写ajax请求

- url : Controller请求
- data:键值对

- success:回调函数

3.给Ajax绑定事件，点击.click，失去焦点onblur，键盘弹起keyup

## 3.2 重要参数介绍

### 3.2.1 url

类型：String

默认值: 当前页地址。发送请求的地址。

### 3.2.2 data

类型：String

发送到服务器的数据。将自动转换为请求字符串格式。

GET 请求中将附加在 URL 后。查看 processData 选项说明以禁止此自动转换。必须为 Key/Value 格式。如果为数组，jQuery 将自动为不同值对应同一个名称。如 {foo:["bar1", "bar2"]} 转换为 '&foo=bar1&foo=bar2'。

> 发送的数据名称要和服务端的参数名字一一对应，不然接受不到

### 3.2.3 success

类型：Function

请求成功后的回调函数。

参数：由服务器返回，并根据 dataType 参数进行处理后的数据；描述状态的字符串。

这是一个 Ajax 事件。

> 建议用console.log(data)来看传回来什么

### 3.2.4 dataType

类型：String

预期服务器返回的数据类型。如果不指定，jQuery 将自动根据 HTTP 包 MIME 信息来智能判断，比如 XML MIME 类型就被识别为 XML。

**在 1.4 中，JSON 就会生成一个 JavaScript 对象，而 script 则会执行这个脚本。**随后服务器端返回的数据会根据这个值解析后，传递给回调函数。可用值:

- "xml": 返回 XML 文档，可用 jQuery 处理。
- "html": 返回纯文本 HTML 信息；包含的 script 标签会在插入 dom 时执行。
- "script": 返回纯文本 JavaScript 代码。不会自动缓存结果。除非设置了 "cache" 参数。注意：在远程请求时(不在同一个域下)，所有 POST 请求都将转为 GET 请求。（因为将使用 DOM 的 script标签来加载）
- "json": 返回 JSON 数据 。
- "jsonp": JSONP 格式。使用 JSONP 形式调用函数时，如 "myurl?callback=?" jQuery 将自动替换 ? 为正确的函数名，以执行回调函数。
- "text": 返回纯文本字符串

### 3.2.5 async

类型：Boolean

默认值: true。默认设置下，所有请求均为异步请求。如果需要发送同步请求，请将此选项设置为 false。

注意，同步请求将锁住浏览器，用户其它操作必须等待请求完成才可以执行。
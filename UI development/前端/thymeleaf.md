# 1、thymeleaf简介

Thymeleaf is a modern server-side Java template engine for both web and standalone environments, capable of processing HTML, XML, JavaScript, CSS and even plain text.

**现代化、服务端Java模板引擎**



## 1.1 Thymeleaf基本语法

#### 1.1.1、 表达式

| 表达式名字 | 语法   | 用途                               |
| ---------- | ------ | ---------------------------------- |
| 变量取值   | ${...} | 获取请求域、session域、对象等值    |
| 选择变量   | *{...} | 获取上下文对象值                   |
| 消息       | #{...} | 获取国际化等值                     |
| 链接       | @{...} | 生成链接                           |
| 片段表达式 | ~{...} | jsp:include 作用，引入公共页面片段 |



#### 1.1.2 、字面量

文本值: **'one text'** **,** **'Another one!'** **,…**

数字: **0** **,** **34** **,** **3.0** **,** **12.3** **,…**

布尔值: **true** **,** **false**

空值: **null**

变量： one，two，.... 变量不能有空格

#### 1.1.3 、文本操作

字符串拼接: **+**

变量替换: **|The name is ${name}|** 



#### 1.1.4 、数学运算

运算符: + , - , * , / , %



#### 1.1.5 、布尔运算

运算符:  **and** **,** **or**

一元运算: **!** **,** **not** 





#### 1.1.6 、比较运算

比较: **>** **,** **<** **,** **>=** **,** **<=** **(** **gt** **,** **lt** **,** **ge** **,** **le** **)**等式: **==** **,** **!=** **(** **eq** **,** **ne** **)** 



#### 1.1.7 、条件运算

If-then: **(if) ? (then)**

If-then-else: **(if) ? (then) : (else)**

Default: (value) **?: (defaultvalue)** 



#### 1.1.8 、特殊操作

无操作： _





# 2、设置属性值-th:attr

设置单个值

```html
<form action="subscribe.html" th:attr="action=@{/subscribe}">
  <fieldset>
    <input type="text" name="email" />
    <input type="submit" value="Subscribe!" th:attr="value=#{subscribe.submit}"/>
  </fieldset>
</form>
```

设置多个值

```html
<img src="../../images/gtvglogo.png"  th:attr="src=@{/images/gtvglogo.png},title=#{logo},alt=#{logo}" />
```



以上两个的代替写法 th:xxxx

```html
<input type="submit" value="Subscribe!" th:value="#{subscribe.submit}"/>
<form action="subscribe.html" th:action="@{/subscribe}">
```



所有h5兼容的标签写法

https://www.thymeleaf.org/doc/tutorials/3.0/usingthymeleaf.html#setting-value-to-specific-attributes



### 2.1 迭代

```html
<tr th:each="prod : ${prods}">
        <td th:text="${prod.name}">Onions</td>
        <td th:text="${prod.price}">2.41</td>
        <td th:text="${prod.inStock}? #{true} : #{false}">yes</td>
</tr>
```



```html
<tr th:each="prod,iterStat : ${prods}" th:class="${iterStat.odd}? 'odd'">
  <td th:text="${prod.name}">Onions</td>
  <td th:text="${prod.price}">2.41</td>
  <td th:text="${prod.inStock}? #{true} : #{false}">yes</td>
</tr>
```



### 2.2 条件运算

```html
<a href="comments.html"
th:href="@{/product/comments(prodId=${prod.id})}"
th:if="${not #lists.isEmpty(prod.comments)}">view</a>
```



```html
<div th:switch="${user.role}">
  <p th:case="'admin'">User is an administrator</p>
  <p th:case="#{roles.manager}">User is a manager</p>
  <p th:case="*">User is some other thing</p>
</div>
```



### 2.3 属性优先级

![img](https://cdn.nlark.com/yuque/0/2020/png/1354552/1605498132699-4fae6085-a207-456c-89fa-e571ff1663da.png?x-oss-process=image%2Fwatermark%2Ctype_d3F5LW1pY3JvaGVp%2Csize_44%2Ctext_YXRndWlndS5jb20g5bCa56GF6LC3%2Ccolor_FFFFFF%2Cshadow_50%2Ct_80%2Cg_se%2Cx_10%2Cy_10)

# 3、thymeleaf使用

## 3.1、引入Starter

```java
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-thymeleaf</artifactId>
</dependency>
```

## 3.2、自动配置好了thymeleaf

ThymeleafAutoConfiguration自动配置

```java
@Configuration(proxyBeanMethods = false)
@EnableConfigurationProperties(ThymeleafProperties.class)
@ConditionalOnClass({ TemplateMode.class, SpringTemplateEngine.class })
@AutoConfigureAfter({ WebMvcAutoConfiguration.class, WebFluxAutoConfiguration.class })
public class ThymeleafAutoConfiguration { }
```



自动配好的策略

- 1、所有thymeleaf的配置值都在 ThymeleafProperties
- 2、配置好了 **SpringTemplateEngine** 

- 3、配好了 **ThymeleafViewResolver** 即视图解析器
- 4、我们只需要直接开发页面

下面是我们对应的视图解析器

```java
	public static final String DEFAULT_PREFIX = "classpath:/templates/";

	public static final String DEFAULT_SUFFIX = ".html";  //默认跳转xxx.html
```

### 3.3、页面开发

每个页面开发我们需要加一个模板

```java
<!DOCTYPE html>
<html lang="en" xmlns:th="http://www.thymeleaf.org">
<head>
    <meta charset="UTF-8">
    <title>Title</title>
</head>
<body>
<h1 th:text="${msg}"></h1>
<h2>
    <a href="www.ceit.com" th:href="${link}">去百度01</a>
    <a href="www.ceit.com" th:href="@{link}">去百度02</a>
</h2>
</body>
</html>
```

对应的Controller

```java
@Controller
public class ViewTestController {
    @GetMapping("/ceit")
    public String ceit(Model model){
        model.addAttribute("msg","你好，ceit");
        model.addAttribute("link","http://www.baidu.com");
        return "success";
    }
}
```

# 4、公共页的使用

我们在设计页面的时候我们会有很多关于我们的相同的部分，这些相同的部分我们叫做公共页。

我们一般把所有公共的部分抽取出来放在一个独立的html当中，我们习惯放在templates文件夹下

## 4.1、文件的thymeleaf形式的改写

为了动态加上项目名，我们可以使用thymeleaf来修改我们的引入文件

1. 对于公共的script(在body标签里面的)引用，我们用

```html
<!-- Placed js at the end of the document so the pages load faster -->
<script th:src="@{/js/jquery-1.10.2.min.js}"></script>
<script th:src="@{/js/jquery-ui-1.9.2.custom.min.js}"></script>
<script th:src="@{/js/jquery-migrate-1.2.1.min.js}"></script>
<script th:src="@{/js/bootstrap.min.js}"></script>
<script th:src="@{/js/modernizr.min.js}"></script>
<script th:src="@{/js/jquery.nicescroll.js}"></script>
```

2. 对于公共的link和script(在head标签里面)

```html
<head>
    <meta charset="UTF-8">
    <title>Title</title>
    <!--common-->
    <link href="css/style.css" th:href="@{/css/style.css}" rel="stylesheet">
    <link href="css/style-responsive.css"  th:href="@{/css/style-responsive.css}" rel="stylesheet">

    <script src="js/html5shiv.js" th:src="@{/js/html5shiv.js}"></script>
    <script src="js/respond.min.js" th:src="@{/js/respond.min.js}></script>
</head>
```

## 4.2、使用公共页

### 4.2.1、配置common页属性

为了是使用公共页，官方给我们的方式有两种

1. 使用`th:fragment="我们自定义的名字"`

```html
<!DOCTYPE html>

<html xmlns:th="http://www.thymeleaf.org">

  <body>
  
    <div th:fragment="copy">
      &copy; 2011 The Good Thymes Virtual Grocery
    </div>
  
  </body>
  
</html>
```

```html
<head th:fragment="commonheader">  //可以在头文件写
    <meta charset="UTF-8">
    <title>Title</title>
    <!--common-->
    <link href="css/style.css" th:href="@{/css/style.css}" rel="stylesheet">
    <link href="css/style-responsive.css"  th:href="@{/css/style-responsive.css}" rel="stylesheet">

    <script src="js/html5shiv.js" th:src="@{/js/html5shiv.js}"></script>
    <script src="js/respond.min.js" th:src="@{/js/respond.min.js}></script>
</head>
```

2. 设置对应的id号

```html
<div id="commonscript"> <!-- 在外层嵌套一个div-->
<!-- Placed js at the end of the document so the pages load faster -->
<script th:src="@{/js/jquery-1.10.2.min.js}"></script>
<script th:src="@{/js/jquery-ui-1.9.2.custom.min.js}"></script>
<script th:src="@{/js/jquery-migrate-1.2.1.min.js}"></script>
<script th:src="@{/js/bootstrap.min.js}"></script>
<script th:src="@{/js/modernizr.min.js}"></script>
<script th:src="@{/js/jquery.nicescroll.js}"></script>
</div>
```

### 4.2.2、在调用的页面使用

1. 我们首先介绍第一种方式的调用和调用效果

```html
<body>
    
<!-- 这里默认我们的公共页的标签是footer，对应的被调用的fragment的值为copy-->
  <div th:insert="footer :: copy"></div>

  <div th:replace="footer :: copy"></div>

  <div th:include="footer :: copy"></div>
  
</body>
```

分别得到以下效果

```html
<body>

  ...
	<!--div插入footer-->
  <div>
    <footer>
      &copy; 2011 The Good Thymes Virtual Grocery
    </footer>
  </div>
	<!--footer取代div-->
  <footer>
    &copy; 2011 The Good Thymes Virtual Grocery
  </footer>
	<!--div把footer吞了，把footer的内容包含了-->
  <div>
    &copy; 2011 The Good Thymes Virtual Grocery
  </div>
  
</body>
```


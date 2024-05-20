
# 1.SpringMvc初始
## 1.1 未来学习框架
![在这里插入图片描述](https://img-blog.csdnimg.cn/ce0d8069c7c14c378db57bd737d74ce9.png)
## 1.2 Web开发结构
**1. JavaWeb开发时候的结构**

![在这里插入图片描述](https://img-blog.csdnimg.cn/9ed007d475e948719530a5746d9bef1e.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAc3BlY2lhbHdpbmU=,size_20,color_FFFFFF,t_70,g_se,x_16)
**2. SpringMvc的Mvc**
![MVC :模型(dao, service) 视图 (jsp)控制器 (Servlet)](https://img-blog.csdnimg.cn/042b107c980b4592824bfe94a6315207.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAc3BlY2lhbHdpbmU=,size_20,color_FFFFFF,t_70,g_se,x_16)
**Model (模型)** :数据模型，提供要展示的数据，因此包含**数据和行为**，可以认为是领域模型或
JavaBean组件(包含数据和行为)，不过现在一般都分离开来: Value Object (数据Dao)和服务
层(行为Service) 。也就是模型提供了模型数据查询和模型数据的状态更新等功能，包括数据和业
务。
>数据就是是对应数据库，行为对应Service层

**View (视图)** :负责进行模型的展示，一般就是我们见到的用户界面，客户想看到的东西。
**Controller (控制器)** :接收用户请求，委托给模型进行处理(状态改变)，处理完毕后把返回的
模型数据返回给视图，由视图负责展示。也就是 说控制器做了个调度员的工作。

**扩展：**


- 我们的前端需要：用户名和密码
- 我们的pojo类实体类中有用户名，密码，生日，爱好，... 20个

设计：
- 我们将pojo细分，pojo,vo，其中vo只有用户名和密码两个属性

## 1.3 两个模型时代
1. Model1
![在这里插入图片描述](https://img-blog.csdnimg.cn/f61bdfb715bd40c382396ea37c0cf5c5.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAc3BlY2lhbHdpbmU=,size_20,color_FFFFFF,t_70,g_se,x_16)
2. Model2

![在这里插入图片描述](https://img-blog.csdnimg.cn/08042e32332e4b5e9c8daa0496a410f3.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAc3BlY2lhbHdpbmU=,size_20,color_FFFFFF,t_70,g_se,x_16)
**职责分析:**

**Controller:控制器**
1. 取得表单数据
2. 调用业务逻辑
3. 转向指定的页面
>就是之前的servlet，我们现在统一叫做Controller

**Model:模型**
1. 业务逻辑
2. 保存数据的状态

**View:视图**
1. 显示页面
## 1.4 MVC框架

**MVC框架要做哪些事情：**
1. 将url映射到java类或java类的方法
2. 封装用户提交的数据
3. 处理请求，调用相关的业务处理，封装响应数据
4. 将响应的数据进行渲染，jsp/html等表示层数据

**说明：**

常见的服务器端MVC框架有: Struts、 Spring MVC、ASP.NET MVC、Zend Framework、
JSF；常见前端MVC框架: vue、angularjs、 react、 backbone； 由MVC演化出了另外一些模式
如: MVP、MVVM等等......
## 1.5 到底什么是SpringMvc
Spring MVC**是Spring Framework的一部分**，是基于Java实现MVC的轻量级Web框架。

**我们为什么要学习SpringMVC呢?**

Spring MVC的特点:
1. 轻量级，简单易学
2. 高效,基于请求响应的MVC框架
3. 与Spring兼容性好，无缝结合。
>我们的Spring是个大杂烩，我们可以把SpringMvc中所有要用的bean注册到Spring中
4. 约定优于配置
5. 功能强大: RESTful、 数据验证、格式化、本地化、主题等
6. 简洁灵活

![在这里插入图片描述](https://img-blog.csdnimg.cn/e67dba7c4eaf43478ee506ab5f0647fb.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAc3BlY2lhbHdpbmU=,size_20,color_FFFFFF,t_70,g_se,x_16)
**Spring的web框架围绕DispatcherServlet [调度Servlet ]设计。DispatcherServle t的作用是将请求分发到不同的处理器。下面是调配器的思想**

![在这里插入图片描述](https://img-blog.csdnimg.cn/3e8c30e37562463d892d2ca552f82f03.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAc3BlY2lhbHdpbmU=,size_20,color_FFFFFF,t_70,g_se,x_16)

>从Spring 2.5开始，使用Java 5或者以上版本的用户可以采用基于注解的controller声明式。

Spring MVC框架像许多其他MVC框架一样，以请求为驱动，围绕一个中心Servlet分派请求及提供其他功能，**DispatcherServlet是一个实际的Servlet (它继承自HttpServlet基类)。**

![在这里插入图片描述](https://img-blog.csdnimg.cn/ddb8bd4869ae4578943634c18065fd4f.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAc3BlY2lhbHdpbmU=,size_20,color_FFFFFF,t_70,g_se,x_16)

## 1.6 SpringMvc的原理思想
![在这里插入图片描述](https://img-blog.csdnimg.cn/d3a3403cc0924cb19d3269a226cfe542.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAc3BlY2lhbHdpbmU=,size_20,color_FFFFFF,t_70,g_se,x_16)
这里重点注意这个ModelAndView

# 2.回顾Servlet
## 2.1新建一个Maven项目导入依赖

```xml
   <dependencies>
        <dependency>
            <groupId>junit</groupId>
            <artifactId>junit</artifactId>
            <version>4.13.2</version>
            <scope>test</scope>
        </dependency>
        <dependency>
            <groupId>org.springframework</groupId>
            <artifactId>spring-webmvc</artifactId>
            <version>5.3.9</version>
        </dependency>
        <dependency>
            <groupId>javax.servlet.jsp</groupId>
            <artifactId>jsp-api</artifactId>
            <version>2.2</version>
        </dependency>
        <dependency>
            <groupId>javax.servlet</groupId>
            <artifactId>jstl</artifactId>
            <version>1.2</version>
        </dependency>
    </dependencies>
```
2. 创造一个干净的Module项目并

- 给他添加Web框架
![在这里插入图片描述](https://img-blog.csdnimg.cn/05d48fcf9a934deabf1da4f2c8a43399.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAc3BlY2lhbHdpbmU=,size_20,color_FFFFFF,t_70,g_se,x_16)
>Servlet生成异常的服务器500错误，我们在3.6有说明
- 给他对应依赖

```xml
<dependencies>
    <dependency>
        <groupId>javax.servlet</groupId>
        <artifactId>servlet-api</artifactId>
        <version>2.5</version>
    </dependency>
    <dependency>
        <groupId>javax.servlet.jsp</groupId>
        <artifactId>jsp-api</artifactId>
        <version>2.2</version>
    </dependency>
</dependencies>
```
## 2.2 编写一个Servlet类用来处理用户的请求
将类继承`HttpServlet`类将他化成专门处理请求的`Servlet`类

```cpp
public class HelloServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        //1.获取前端参数
        String method = req.getParameter("method");
        if (method.equals("add")){
            req.getSession().setAttribute("msg","执行了add方法");
        }
        if (method.equals("delete")){
            req.getSession().setAttribute("msg","执行了delete方法");
        }
        // 2.调用业务层
        // 3.视图转发或者重定向
        //转发req.getRequestDispatcher()
        //重定向resp.sendRedirect();
        //req.getRequestDispatcher("/WEB-INF/jsp/test.jsp").forward(req,resp);
        //第一个/代表当前项目下的,forward是带过去的数据
        req.getRequestDispatcher("/WEB-INF/jsp/test.jsp").forward(req,resp);
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        doGet(req,resp);
    }
}

```
## 2.3 创造jsp文件并编写测试文件
客户端文件`form.jsp`

```jsp
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Title</title>
</head>
<body>
<form action="/hello" method="post">
    <input type="text" name="method">
    <input type="submit">
</form>
</body>
</html>

```
数据渲染`test.jsp`

```xml
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Title</title>
</head>
<body>
${msg}
</body>
</html>
```
## 2.4 修改web.xml设置

```xml
  <servlet>
    <servlet-name>hello</servlet-name>
    <servlet-class>com.kuang.servlet.HelloServlet</servlet-class>
  </servlet>
  <servlet-mapping>
    <servlet-name>hello</servlet-name>
    <url-pattern>/hello</url-pattern>
  </servlet-mapping>
  <session-config>
    <session-timeout>15</session-timeout>
  </session-config>
  <welcome-file-list>
    <welcome-file>index.jsp</welcome-file>
  </welcome-file-list>
```

## 2.5 配置tomcat并配置服务器启动验证

```txt
http://localhost:8080/hello?method=add
http://localhost:8080/hello?method=delete
```

# 3.搭建SpringMvc框架
## 3.1 创建新module并配置好对应的web的依赖

```xml
<dependencies>
    <dependency>
        <groupId>javax.servlet</groupId>
        <artifactId>servlet-api</artifactId>
        <version>2.5</version>
    </dependency>
    <dependency>
        <groupId>javax.servlet.jsp</groupId>
        <artifactId>jsp-api</artifactId>
        <version>2.2</version>
    </dependency>
</dependencies>
```

## 3.2 配置web.xml
首先我们启动我们的Mvc的DispatcherServlet服务，我们的`org.springframework.web.servlet.DispatcherServlet`是spring帮我们自定义好的内部类，我们这里直接注册
```xml
<!--注册DispatcherServlet-->
    <servlet>
        <servlet-name>springmvc</servlet-name>
        <servlet-class>org.springframework.web.servlet.DispatcherServlet</servlet-class>
        <!--绑定SpringMvc的配置文件，其实就算Spring配置文件，关于SpringMvc配置文件起名问题，
        我们推荐用上面的servlet-name的名字加上我们的-servlet为命名，是早些版本命名方式，
        在后面的开发方式中我们的因为分工问题都会把所有的Spring配置文件去导入到ApplicationContext.xml中-->
        <init-param>
            <param-name>contextConfigLocation</param-name>
            <param-value>classpath:springmvc-servlet.xml</param-value>
        </init-param>
<!--系统一启动我们有些请求就会被处理（内置请求），
我们要让它和服务器一起起来，我们设置启动级别为1-->
        <load-on-startup>1</load-on-startup>
    </servlet>
<!--    /匹配所有的请求：（不包括.jsp)-->
<!--    /*匹配所有请求，（包括.jsp)-->
    <servlet-mapping>
        <servlet-name>springmvc</servlet-name>
        <url-pattern>/</url-pattern>
    </servlet-mapping>

```
注意这里不能写/*，不然在后面我们请求视图jsp时候，我们又会访问我们的前端控制器，导致我们的请求再一次嵌套，再请求，我们会让程序变成死循环。
## 3.3 配置springmvc-servlet.xml文件
我们的`org.springframework.web.servlet.DispatcherServlet`的配置中需要对应`springmvc-servlet.xml`文件，我们在资源resource中进行新的xml创建

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xsi:schemaLocation="http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd">
</beans>
```
>这里建议在创建项目中新建一个样本模型，以方便以后使用

我们要在`springmvc-servlet.xml`中注册三个对应类

**1.处理映射器**

```xml
	<bean class="org.springframework.web.servlet.handler.BeanNameUrlHandlerMapping"/>
```
因为我们这个处理器是`BeanNameUrlHandlerMapping`，所以我们要在下面注册
假如我们请求/hello，我们交给`HelloController`处理
```xml
	<bean id=“/hello” class="com.kuang.controller.HelloController">
```

**2.处理器适配器**
```xml
    <bean class="org.springframework.web.servlet.mvc.SimpleControllerHandlerAdapter"/>
```
**3.视图解析器**

```xml
    <bean class="org.springframework.web.servlet.view.InternalResourceViewResolver" id="internalResourceViewResolver">
    	<!--前缀-->
        <property name="prefix" value="/WEB-INF/jsp/"/>
        <!--后缀-->
        <property name="suffix" value=".jsp"/>
    </bean>
```
>视图解析器:DispatcherServlet给他的ModeLAndView
## 3.4 编写我们要操作业务Controller
要么实现`Controller`接口，要么增加注解
需要返回一个`ModelAndView`，装数据，封视图;

**1. 注意我们的接口导入的包是**

```c
import org.springframework.web.servlet.mvc.Controller;
```
**2.注意我们这是为了了解原理才这样写，项目中不用这样**
```c
public class HelloController implements Controller {
    public ModelAndView handleRequest(HttpServletRequest request, HttpServletResponse response ) throws Exception {
    //ModeLAndview模型和视图
    ModelAndView mv = new ModelAndView( ) ;
    //封装对象，放在ModelAndView中。ModeL
    mv.addObject("msg","HelloSpringMVC!");
    //封装要跳转的视图,放在ModeLAndView中
    mv.setViewName("hello"); //: /WEB-INF/jsp/hello.jsp
    return mv;

}}
```
>这里的区别是我们用ModelAndView就可以存放东西，而之前要用session那些进行存放，存放的页面转换

>以前要进行转发跳转，现在只要设置视图的名字就好了，因为我们在springmvc-servlet中已经设置了对应的前缀和后缀，会自动拼接

我们要放入springmvc-servlet进行bean注入

```xml
<!--handler-->
    <bean id="/hello" class="com.kuang.controller.HelloController"/>
```
>这里一定要加/，不然默认错误找不到就404了，因为映射器是将控制器的bean的id作为映射的url
## 3.5 测试
大致进程
**注意是大致进程**
![在这里插入图片描述](https://img-blog.csdnimg.cn/5a52ed583311418f933f4ae2f89f6a65.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAc3BlY2lhbHdpbmU=,size_20,color_FFFFFF,t_70,g_se,x_16)
结果
![在这里插入图片描述](https://img-blog.csdnimg.cn/67083eddb6064aa0b85e278b57357b26.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAc3BlY2lhbHdpbmU=,size_20,color_FFFFFF,t_70,g_se,x_16)

## 3.6 常见问题

**404报错：**
1. 查看控制台输出，看一下是不是缺少了什么jar包。
2. 如果jar包存在，显示无法输出，就在IDEA的项目发布中，添加lib依赖
3. 重启Tomcat即可解决!

**原因：**

	我们调度tomcat有在进行打包配置文件的时候产生了偏差问题

**解决办法：**
1. 进入Project Structure中
2. 进入Project Settings中
3. 进入Artifacts中

**一般情况下我们的web项目**
![在这里插入图片描述](https://img-blog.csdnimg.cn/91dcd6eacdbe49b99757dcc4cb89d83b.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAc3BlY2lhbHdpbmU=,size_20,color_FFFFFF,t_70,g_se,x_16)
**出问题的项目**
![在这里插入图片描述](https://img-blog.csdnimg.cn/ed7fd896e22a4286b9dcf301de37a285.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAc3BlY2lhbHdpbmU=,size_20,color_FFFFFF,t_70,g_se,x_16)
**我们缺少了lib，新建lib文件夹以后进行把包导入操作**
![在这里插入图片描述](https://img-blog.csdnimg.cn/84242162a57c4cbd81bcabf4f780d4c1.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAc3BlY2lhbHdpbmU=,size_20,color_FFFFFF,t_70,g_se,x_16)
**点击Apply以后重启**

# 4.深入学习SpringMvc
## 4.1 SpringMvc执行原理

1. 点击`http://localhost:8080/hello`
2. 进入`web.xml`的`DispatcherServlet`中，改请求进入分流
3. 我们在`DispatcherServlet`中绑定`springmvc-servlet.xml`配置，在我们`springmvc-servlet.xml`中我们进行处理器映射，映射到`/hello`,处理器适配器去找到`bean id="/hello"`的`controller`接口
4. `controller`接口处理得到结果通过`DispatcherServlet`返回
![在这里插入图片描述](https://img-blog.csdnimg.cn/565822d1cd1f4d6aa6f1d8ab3f3c26dd.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAc3BlY2lhbHdpbmU=,size_20,color_FFFFFF,t_70,g_se,x_16)

内部处理详解：
1. HandlerMapping为处理器映射。DispatcherServlet调用
HandlerMapping,HandlerMapping根据请求url查找Handler。
2. HandlerExecution表示具体的Handler,其主要作用是根据url查找控制器，如上url被查找控制器为:hello。
3. HandlerExecution将解析后的信息传递给DispatcherServlet,如解析控制器映射等。
4. HandlerAdapter表示处理器适配器，其按照特定的规则去执行Handler。这里的特定规矩其实就是去找我们的HelloController，**是去找我们的代码中实现了我们Controller接口的去适配**，我们的 `HelloController`的类只是为了重写Controller类的`handleRequest(HttpServletRequest var1, HttpServletResponse var2) throws Exception;`方法
5. Handler让具体的Controller执行。
6. Controller将具体的执行信息返回给HandlerAdapter,如ModelAndView。   
7. HandlerAdapter将视图逻辑名或模型传递给DispatcherServlet。**此时携带了我们要传回前端的数据和需要找谁**
8. DispatcherServlet调用视图解析器(ViewResolver)来解析HandlerAdapter传递的逻辑视图名。**1.视图解析器获取了ModelAndView中的数据。2.解析ModelAndView中的视图名字。3.拼接视图的视图来找到对应的视图。4.将数据渲染到视图中。**
9. 视图解析器将解析的逻辑视图名传给DispatcherServlet。                                                                                                    



## 4.2 注解实现我们的SpringMvc
1. 创建新的module，并给他添加对应依赖
2. 这里注意Web.xml版本，我们的idea如果直接使用maven的Web框架的时候，我们可能使用就是低版本，但是我们如果用添加框架的时候，就是4.0版本
3. 进入项目结构添加lib，注意我们的lib和class同级目录
4. 编写`web.xml`

```xml
    <servlet>
        <servlet-name>springmvc</servlet-name>
        <servlet-class>org.springframework.web.servlet.DispatcherServlet</servlet-class>
        <init-param>
            <param-name>contextConfigLocation</param-name>
            <param-value>classpath:springmvc-servlet.xml</param-value>
        </init-param>
        <load-on-startup>1</load-on-startup>
    </servlet>
    <servlet-mapping>
        <servlet-name>springmvc</servlet-name>
        <url-pattern>/</url-pattern>
    </servlet-mapping>
```
5. 编写springmvc-servlet.xml

```xml

<!--    自动扫描包，让指定包下的注解生效，由IOC容器管理-->
    <context:component-scan base-package="com.kuang.controller"/>
<!--    让SpringMvc不处理静态资源  .css .js  .html .mp3  .mp4-->
    <mvc:default-servlet-handler/>

<!--    支持mvc注解驱动-->
<!--    在spring中一般采用@RequestMapping注解来完成映射关系-->
<!--    要想使@RequestMapping注解生效-->
<!--    必须向上下文中注册DefauLtAnnotationHandLerMapping利一个AnnotationMethodHandLerAdapter实例-->
<!--    这两个实例分别在类级别和方法级别处理。-->
<!--    而annotation-driven配置帮助我们自动完成上述两个实例的注入。-->

    <mvc:annotation-driven/>

<bean class="org.springframework.web.servlet.view.InternalResourceViewResolver" id="internalResourceViewResolver">
    <property name="prefix" value="/WEB-INF/jsp/"/>
    <property name="suffix" value=".jsp"/>
</bean>
```
6. 编写Controller

```java
@Controller
public class HelloController {
    @RequestMapping("/hello")
    public String hello(Model model){
        //封装数据
        model.addAttribute("msg","Hello,SpringmvcAnnotation");
        return "hello";  //被视图解析器处理
    }
}

```
注意我们的`@RequestMapping`可以用在类的外面也可以在方法里面，它的具体类如下

```java
@Target({ElementType.TYPE, ElementType.METHOD})
@Retention(RetentionPolicy.RUNTIME)
@Documented
@Mapping
public @interface RequestMapping {
.....}
```
我们要是在`@RequestMapping`在类的时候，要请求里面的方法的时候，要根据不同方法的调用前都要加上类的`@RequestMapping`，如

```java
@Controller
@RequestMapping("/hello")
public class HelloController {
    @RequestMapping("/h1")
    public String hello(Model model){
        //封装数据
        model.addAttribute("msg","Hello,SpringmvcAnnotation");
        return "hello";  //被视图解析器处理
    }
}
```
>此时的路径是localhost:8080/hello/h1

json传数据，用`@RestController`时候我们的类不会被视图解析器解析，返回的就是字符串

## 4.3 Controller

- 控制器复杂提供访问压用程序的行为，通常**通过接口定义或注解定义**两种方法实现。
- 控制器负责解析用户的请求并将其转换为一个模型。
- 在Spring MVC中一个控制器类可以包含多个方法
- 在Spring MVC中，对于Controller的配置方式有很多种
>接口和注解两种方式上面都有说明，我们推荐使用接口，简单又方便

我们写注解说明他们被spring代理
```java
//组件
@Component
//dao对应
@Repository
//service对应
@Service
//controller对应
@Controller
```
**特别注意，被这个注解的类的所有方法如果返回值是String，并且有具体页面可以跳转，那么就会被视图解析器解析**

## 4.4 RequestMapping
- `@RequestMapping`注解用于映射url到控制器类或一个特定的处理程序方法。可用于类或方法上。
- 用于类上，表示类中的所有响应请求的方法都是以该地址作为父路径。

我们在开发网站的时候，我们会调用不同的服务，例如，我们的开发有专用的admin管理员，和面向用户user主页等等，使用mvc框架以后我们可以在Controller接口上配置我们不同的`@RequestMapping("/admin")`和`@RequestMapping("/user")`等，可直接操作不同的接口，但是我们不推荐我们在类的上面写，因为在调试不同的代码的时候，容易忽略，**建议直接在方法上写死代码**。

# 5.RestFul风格
## 5.1 概念和功能
**1. 概念**

Restful就是一个资源定位及资源操作的风格。不是标准也不是协议，只是一种风格。基于这个风格设计的软件可以更简洁，更有层次，更易于实现缓存等机制。

**2. 功能**
- 资源:互联网所有的事物都可以被抽象为资源
- 资源操作:使用POST、DELETE、PUT、GET，使用不同方法对资源进行操作。
- 分别对应添加、删除、修改、查询。
## 5.2 传统方式操作资源和使用Restful操作资源
以前
```sh
http://localhost:8080/hello?method=add
```
现在RestFul
```sh
http://localhost:8080/hello/method/delete
```
**3. 传统方式操作资源**︰通过不同的参数来实现不同的效果，方法单一，post和get
- http://127.0.0.1/item/queryltem.action?id=1 查询,GET
- http://127.0.0.1/item/saveltem.action      新增,POST
- http://127.0.0.1/item/updateltein.action 更新,POST
- http://127.0.0.1/item/deleteltem.action?id=1 删除,GET或POST

**4. 使用Restful操作资源**︰可以通过不同的请求方式来实现不同的效果，如下:请求地址一样，但是功能可以不同
- http://127.0.0.1/item/1 查询,GET. 
- http://127.0.0.1/item 新增,POST. 
- http://127.0.0.1/item 更新,PUT
- http://127.0.0.1/item/1 删除,DELETE

## 5.3 实现RestTful

1. 新建一个类 RestFulController 

```java
@Controller
public class RestFulController {
}
```
2. 在Spring MVC中可以使用`@PathVariable`注解，让方法参数的值对应绑定到—个URI模板变量

```java
@Controller
public class RestFulController {

    // 原来 http://localhost:8080/add?a=1&b=2
    // RestFul http://localhost:8080/add/1/2
    // @PathVariable 路径变量 为了获取它的值
@RequestMapping("/add/{a}/{b}")
public String test1(@PathVariable int a,@PathVariable int b, Model model){
    int res = a + b;
    model.addAttribute("msg","结果是"+res);
    return "test";
}
}

```
## 5.4 小结
Spring MVC的`@RequestMapping`注解能够处理HTTP请求的方法，比如GET,PUT,POST,DELETE以及PATCH

**所有的地址栏请求默认都会是HTTP GET 类型的**

方法级别的注解变体有如下几个:组合注解

```txt
@GetMapping
@PostMapping
@PutMapping
@DeleteMapping
@PatchMapping
```
**推荐使用**

**思考:使用路径变量的好处?**
- 使路径变得更加简洁;
- 获得参数更加方便，框架会自动进行类型转换。
- 通过路径变量的类型可以约束访问参数，如果类型不一样，则访问不到对应的请求方法，如这里访问是的路径是/commit/1/a，则路径与方法不匹配，而不会是参数转换失败。
- 安全，隐藏了参数
# 6.结果跳转方式

## 6.1 ModelAndView
设置ModelAndView对象，根据view的名称，和视图解析器跳劲指定的页面

页面：{视图解析器前缀} + viewName + {视图解析器后缀}


>推荐，简单使用
## 6.2 ServletAPI
通过设置ServletAPI，不需要视图解析器﹒

1. 通过HttpServletResponse进行输出
2. 通过HttpServletResponse实现重定向
3. 通过HttpServletResponse实现转发

所有请求都会进Servlet中`doService(req,resp)`方法
>不推荐，此时方法的变成了HttpServlet的req和resp

```c
@RequestMapping(value = "/add",method = RequestMethod.GET)
public String test1(){
	//默认转发
	return "test";
	//重定向：我们的重定向不能访问WEB-INF下的jsp，相当于不走视图解析器
    return "redirect:/test.jsp";
}
```

## 6.3 SpringMVC
通过SpringMVC实现转发和重定向，且无需视图解析器

```java
@RequestMapping(value = "/add",method = RequestMethod.GET)
public String test1(){
	//转发1
    return "/index.jsp";
    //转发2 return "forward:/index.jsp"
}
```

```java
@RequestMapping(value = "/add",method = RequestMethod.GET)
public String test1(){
	//重定向
    return "redirect:/index.jsp";
}
```
>不推荐，而且我们要是jsp要在WEB-INF下还要写权限定名字
# 7.数据处理
## 7.1 处理提交数据
**1. 提交的域名称和处理方法的参数名一致**

提交数据：http://localhost:8080/user/t1?name=ceit

```java
@Controller
@RequestMapping("/user")
public class UserController {
    //localhost:8080/user/t1?name=xxx
    @GetMapping("/t1")
    public String test1(String name, Model model){
        //1.接受前端参数
        System.out.println("接受到前端的参数为");
        model.addAttribute("msg",name);
        //2.将返回的结果传递给前端
        return "test";
    }
}
```
>不推荐这种写法，因为要是什么都不提交的话，我们也会传一个String为null

**2. 提交的域名称和处理方法的参数名不一致**

提交数据：http://localhost:8080/user/t1?username=ceit

```java
@Controller
@RequestMapping("/user")
public class UserController {
    //localhost:8080/user/t1?name=xxx
    @GetMapping("/t1")
    public String test1(@RequestParam("username") String name, Model model){
        //1.接受前端参数
        System.out.println("接受到前端的参数为");
        model.addAttribute("msg",name);
        //2.将返回的结果传递给前端
        return "test";
    }
}
```
>推荐这种写法，清晰简单。当我们前后端一样的时候，我们也推荐这种写法

提交数据：http://localhost:8080/user/t1?name=ceit

```java
@Controller
@RequestMapping("/user")
public class UserController {
    //localhost:8080/user/t1?name=xxx
    @GetMapping("/t1")
    public String test1(@RequestParam("name") String name, Model model){
        //1.接受前端参数
        System.out.println("接受到前端的参数为");
        model.addAttribute("msg",name);
        //2.将返回的结果传递给前端
        return "test";
    }
}
```
**3. 提交一个对象**

要求我们提交的表单域和对象的属性名一致，参数使用对象即可

提交数据：http://localhost:8080/user/t2?name=ceit&id=1&age=20
```java
    //前端接受到是一个对象： id ,name, age
    //接收前端用户传递的参数，判断参数的名字，假设名字直接在方法上可直接使用
    //假设传递的是一个对象User，匹虚User对象中的字段名;如果名宁一效则ok，否则，匹配不到
    @GetMapping("/t2")
    public String test2(User user){
        System.out.println(user);
        return "test";
    }
```
**说明:如果使用对象的话，前端传递的参数名和对象名必须一致，否则就是null。**

## 7.2 数据显示到前端
**1. ModelAndView**

```java
public class HelloController implements Controller {
    public ModelAndView handleRequest(HttpServletRequest request, HttpServletResponse response ) throws Exception {
    //ModeLAndview模型和视图
    ModelAndView mv = new ModelAndView( ) ;
    //封装对象，放在ModelAndView中。ModeL
    mv.addObject("msg","HelloSpringMVC!");
    //封装要跳转的视图,放在ModeLAndView中
    mv.setViewName("hello"); //: /WEB-INF/jsp/hello.jsp
    return mv;

}}
```

**2. Model**

```java
@Controller
@RequestMapping("/user")
public class UserController {
    //localhost:8080/user/t1?name=xxx
    @GetMapping("/t1")
    public String test1(@RequestParam("name") String name, Model model){
        //1.接受前端参数
        System.out.println("接受到前端的参数为");
        model.addAttribute("msg",name);
        //2.将返回的结果传递给前端
        return "test";
    }
}
```
**3. ModelMap**

```c
LinkedHashMap
ModelMap
Model 
```

**4. 对比**
1. `Model`只有寥寥几个方法只适合用于储存数据，简化了新手对于`Model`对象的操作和理解;
2. `ModelMap`继承了`LinkedMap` ，除了实现了自身的一些方法，同样的继承`LinkedMap`的方法和特性;
3. `NodelAndview` 可以在储存数据的同时，可以进行设置返回的逻辑视图，进行控制展示层的跳转。
## 7.3 过滤器解决乱码问题

**1. 前端的表单**

```jsp
<form action="/e/t" method="post">
    <input type="text" name="name">
    <input type="submit">
</form>
```
**2. Controller**

```c
@Controller
public class EncordingController {
    @PostMapping("/e/t1")
    public String test1(@RequestParam("name") String name , Model model){
        model.addAttribute("msg",name);
        return "test";
    }
}
```

**3. 乱码**
![在这里插入图片描述](https://img-blog.csdnimg.cn/21b9cc7dbcda4fc3bcbf5eafc3cab54d.png)
**4. 解决乱码**

新建过滤器类并编写对应的过滤器`doFilter`方法
```java
public class EncodingFilter implements Filter {
    @Override
    public void init(FilterConfig filterConfig) throws ServletException {

    }

    @Override
    public void doFilter(ServletRequest servletRequest, ServletResponse servletResponse, FilterChain filterChain) throws IOException, ServletException {
        servletRequest.setCharacterEncoding("utf-8");
        servletResponse.setCharacterEncoding("utf-8");

        filterChain.doFilter(servletRequest,servletResponse);
    }

    @Override
    public void destroy() {

    }
}

```
在`web.xml`配置注册对应的`Filter`类

```xml
    <filter>
        <filter-name>encoding</filter-name>
        <filter-class>com.ceit.filter.EncodingFilter</filter-class>
    </filter>
    <filter-mapping>
        <filter-name>encoding</filter-name>
        <url-pattern>/*</url-pattern>
    </filter-mapping>
```
>这是表单在post请求下的乱码错误

**5. 使用SpringMvc彻底解决配置问题**

在`web.xml`配置注册对应的`Filter`类

```xml
<filter>
    <filter-name>encoding</filter-name>
    <filter-class>org.springframework.web.filter.CharacterEncodingFilter</filter-class>
    <init-param>
        <param-name>encoding</param-name>
        <param-value>utf-8</param-value>
    </init-param>
</filter>
    <filter-mapping>
        <filter-name>encoding</filter-name>
        <url-pattern>/*</url-pattern>
    </filter-mapping>
```
>/*能处理jsp和所有请求
>/只能处理请求
# 8.前后端分离问题
前后端分离时代:
- 后端部署后端，提供接口，提供数据
- 前端独立部署，负责渲染后端的数据
## 8.1 什么是JSON
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

## 8.2 Jackson
- Jackson应该是目前比较好的json解析工具了
- 当然工具不止这一个，比如还有阿里巴巴的 fastjson等等
- 我们这里使用Jackson，使用它需要导入它的jar包

```xml
    <dependency>
        <groupId>com.fasterxml.jackson.core</groupId>
        <artifactId>jackson-databind</artifactId>
        <version>2.12.1</version>
    </dependency>
```
用`ObjectMapper`的`writeValueAsString(String string)`方法把对象用json格式输出
```java
    @ResponseBody //不会走视图解析器，会直接返回一个字符串
    @RequestMapping("/j1")
    public String json1() throws JsonProcessingException {
        //jackson ,ObjectMapper
        ObjectMapper mapper = new ObjectMapper();
        //创建一个对象
        User user = new User(3, "陆家贤", "男");

        String s = mapper.writeValueAsString(user);
        return s;
    }
```

```java
    @ResponseBody //不会走视图解析器，会直接返回一个字符串
    @RequestMapping("/j2")
    public String json2() throws JsonProcessingException {
        //jackson ,ObjectMapper
        ObjectMapper mapper = new ObjectMapper();

        List<User> userList = new ArrayList<>();
        //创建一个对象
        User user1 = new User(3, "陆家贤", "男");
        User user2 = new User(3, "陆家贤", "男");
        User user3 = new User(3, "陆家贤", "男");
        User user4 = new User(3, "陆家贤", "男");

        userList.add(user1);
        userList.add(user2);
        userList.add(user3);
        userList.add(user4);


        String s = mapper.writeValueAsString(userList);
        return s;
    }
```

这里注意`@ResponseBody`只会返回`json`格式，当我们在类的上面加上`@RestController`，该类的所有方法的都会只能返回json格式数据，不会走视图解析器

JSON乱码问题配置

```xml
    <mvc:annotation-driven>
        <mvc:message-converters register-defaults="true">
            <bean class="org.springframework.http.converter.StringHttpMessageConverter">
            <constructor-arg value="UTF-8"/>
            </bean>
            <bean class="org.springframework.http.converter.json.MappingJackson2HttpMessageConverter">
                <property name="objectMapper">
                    <bean class="org.springframework.http.converter.json.Jackson2ObjectMapperFactoryBean">
                        <property name="failOnEmptyBeans" value="false"/>
                    </bean>
                </property>
            </bean>
         </mvc:message-converters>
    </mvc:annotation-driven>
```
## 8.3 时间类返回JSON数据及重载思想的定义
我们编写专门的工具类复用JsonUtils 
```java
public class JsonUtils {
    public static String getJson(Object object) throws JsonProcessingException {
        return getJson(object,"yyy-MM-dd HH:mm:ss");
    }
    public static String getJson(Object object,String dateFormat) throws JsonProcessingException {
        ObjectMapper mapper = new ObjectMapper();
 //不使用时间戳的方式       
 mapper.configure(SerializationFeature.WRITE_DATES_AS_TIMESTAMPS,false);
 //自定义日期格式对象
        SimpleDateFormat sdf = new SimpleDateFormat(dateFormat);
        mapper.setDateFormat(sdf);
            return mapper.writeValueAsString(object);
    }
}
```
在mapper层面上进行了修改，我们的Date还是Date，但是我们最后在mapper输出的时候，我们的mapper不使用时间戳的方式给它定义了一个日期格式。
```java
    @ResponseBody //不会走视图解析器，会直接返回一个字符串
    @RequestMapping("/j3")
    public String json3() throws JsonProcessingException {
        Date date = new Date();
        return JsonUtils.getJson(date);
    }
```
此时我们的前面的代码随之修改
```java
    @ResponseBody //不会走视图解析器，会直接返回一个字符串
    @RequestMapping("/j2")
    public String json2() throws JsonProcessingException {
        List<User> userList = new ArrayList<>();
        //创建一个对象
        User user1 = new User(3, "陆家贤", "男");
        User user2 = new User(3, "陆家贤", "男");
        User user3 = new User(3, "陆家贤", "男");
        User user4 = new User(3, "陆家贤", "男");
        userList.add(user1);
        userList.add(user2);
        userList.add(user3);
        userList.add(user4);
       	return JsonUtils.getJson(userList);

    }
```
**我们的mapper只是在日期的输出格式上改变，如果对象不是日期的话，相当于只有**

```java
    public static String getJson(Object object,String dateFormat) throws JsonProcessingException {
        ObjectMapper mapper = new ObjectMapper();

        return mapper.writeValueAsString(object);
    }
```
## 8.4 FastJson
fastjson.jar是阿里开发的一款专门用于Java开发的包，可以方便的实现json对象与JavaBean对象的转换，实现JavaBean对象与json字符串的转换，实现json对象与json字符串的转换。实现json的转换方法很多，最后的实现结果都是一样的。

fastjson的 pom依赖

```xml
        <dependency>
            <groupId>com.alibaba</groupId>
            <artifactId>fastjson</artifactId>
            <version>1.2.60</version>
        </dependency>
```
**fastjson三个主要的类**

 `JSONObject` 代表json对象
- JSONObject实现了Map接口,猜想
JSONObject底层操作是由Map实现的。
- JSONObject对应json对象，通过各种形式的get()方法可以获取json对象中的数据，也可利用诸如size()， isEmpty()等方法获取"键:值"对的个数和判断是否为空。其本质是通过实现Map接口并调用接口中的方法完成的。

`JSONArray` 代表作json对象数组
- 内部是有List接口中的方法来完成操作的。. 

`JSON`代表JSONObject和JSONArray的转化

- JSON类源码分析与使用
- 仔细观察这些方法，主要是实现json对象，json对象数组，javabean对象，json字符串之间的相互转化。


```java

    @ResponseBody //不会走视图解析器，会直接返回一个字符串
    @RequestMapping("/j2")
    public String json2() throws JsonProcessingException {
        //jackson ,ObjectMapper
        ObjectMapper mapper = new ObjectMapper();

        List<User> userList = new ArrayList<>();
        //创建一个对象
        User user1 = new User(3, "陆家贤", "男");
        User user2 = new User(3, "陆家贤", "男");
        User user3 = new User(3, "陆家贤", "男");
        User user4 = new User(3, "陆家贤", "男");

        userList.add(user1);
        userList.add(user2);
        userList.add(user3);
        userList.add(user4);


        String s = JSON.toJSONString(userList);
        return s;
    }
```
# 1.Spring介绍
## 1.1 简介
- 2002，首次推出了Spring框架的雏形: interface21框架!
- Spring框架即以interface21框架为基础,经过重新设计;并不断丰富其内涵,于2004年3月24日,发布了1.0正式版。
- Rod Johnson ,Spring Framework创始人，著名作者。很难想象Rod Johnson的学历，真的让好多人大吃一惊，他是悉尼大学的博士，然而他的专业不是计算机，而是音乐学。
- spring理念:使现有的技术更加容易使用，本身是一个大杂烩，整合了现有的技术框架!

**预备安装**
1. 官网: https://spring.io/projects/spring-framework#overview
2. 官方下载地址:http://repo.spring.io/release/org/springframework/spring
3. GitHub: https://github.com/spring-projects/spring-framework
4. maven对应依赖
```xml
<!-- https://mvnrepository.com/artifact/org.springframework/spring-webmvc -->
<dependency>
    <groupId>org.springframework</groupId>
    <artifactId>spring-webmvc</artifactId>
    <version>5.2.12.RELEASE</version>
</dependency>
```
>这里建议使用springWebMvc，当我们下载这个包时候会自动帮我们进行对应的依赖导包
```xml
<dependency>
    <groupId>org.springframework</groupId>
    <artifactId>spring-jdbc</artifactId>
    <version>5.2.12.RELEASE</version>
</dependency>
```
>我们最好要和mybatis整合，所以需要和数据库等进行连接，我们因此要导入对应的jdbc
>
## 1.2 优点
- Spring是一个开源的免费的框架（容器)!
- Spring是一个轻量级的、非入侵式的框架!
- **控制反转IOC，面向切面编程AOP**
- 支持事务的处理，对框架整合的支持

## 1.3 组成
![在这里插入图片描述](https://img-blog.csdnimg.cn/429c0aed4b764b2c8a7af973e2bcb2f4.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAc3BlY2lhbHdpbmU=,size_20,color_FFFFFF,t_70,g_se,x_16)
## 1.4 扩展
![在这里插入图片描述](https://img-blog.csdnimg.cn/603befaaba114c8cba5ac7f60e6ce4ea.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAc3BlY2lhbHdpbmU=,size_20,color_FFFFFF,t_70,g_se,x_16)
- 1.用spring Boot构造一切
	- 一个快速开发的脚手架。
	- 基于SpringBoot可以快速的开发单个微服务。
	- 约定大于配置
- 2.用Spring Cloud协调一切
	-  	SpringCloud是基于SpringBoot实现的。
	

因为现在大多数公司都在使用SpringBoot进行快速开发，学习SpringBoot的前提，需要完全掌握Spring及SpringMVc!l

**发展太久以后，违背了原来的理念，配置十分繁琐，人称配置地狱**

# 2.IOC理论推导
1. UserDao接口
2. UserDaolmpl接现类
3. UserService 业务接口
4. Userservicelmpl 业务实现类

平时我们的业务实现
![在这里插入图片描述](https://img-blog.csdnimg.cn/5d1d2ec00b1d43ebb16c3044131a3c9f.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAc3BlY2lhbHdpbmU=,size_20,color_FFFFFF,t_70,g_se,x_16)
![在这里插入图片描述](https://img-blog.csdnimg.cn/c94f8033cb9a4bb3aae623c6446c64e8.png)

>假如需求不断增加对应的业务实现类就会特别麻烦，特别繁杂，在UserServicelmpl里面我们需要不断修改我们调用的Dao业务实现类去实现用户的需求这样我们的程序是无法适应用户的变更

**为了解决这个问题，我们可以在业务层实现一个set方法，发生革命性变化**

```java
//利用set动态实现值的注入
public void setUserDao(UserDao userDao){
    this.userDao = userDao;
}
```

- 之前程序是主动创建对象，程序权在程序员手上
- 使用set注入后程序不再具有主动性而是变成被动接受对象

**在测试代码（用户层）**

```java
((UserServiceImpl)userService).setUserDao(new UserDaoMysqlImpl());
((UserServiceImpl)userService).setUserDao(new UserDaoImpl());
```
**这时候，我们将对象的创建管理交给了用户，这种思想，从本质上解决了问题，系统的耦合性大大降低，可以更加专注的在业务的实现上!这就是IOC的原型**
![在这里插入图片描述](https://img-blog.csdnimg.cn/9d21172fcd934d75a25559284b44085d.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAc3BlY2lhbHdpbmU=,size_20,color_FFFFFF,t_70,g_se,x_16)
![在这里插入图片描述](https://img-blog.csdnimg.cn/b86c15b8afaa4849a4e7cafdbad3f78e.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAc3BlY2lhbHdpbmU=,size_20,color_FFFFFF,t_70,g_se,x_16)
## 2.1 IOC的本质
**控制反转loC(Inversion of Control)，是一种设计思想，Dl(依赖注入)是实现loC的一种方法**，也有人认为DI只是loC的另一种说法。没有loC的程序中，我们使用面向对象编程，对象的创建与对象间的依赖关系完全硬编码在程序中，对象的创建由程序自己控制，控制反转后将对象的创建转移给第三方，个人认为所谓控制反转就是:获得依赖对象的方式反转了。

采用XML方式配置Bean的时候，Bean的定义信息是和实现分离的，而采用注解的方式可以把两者合为一体，Bean的定义信息直接以注解的形式定义在实现类中，从而达到了零配置的目的。

**控制反转是一种通过描述（XML或注解）并通过第三方去生产或获取特定对象的方式。在Spring中实现控制反转的是loC容器，其实现方法是依赖注入(Dependency Injection,Dl)。**
## 2.2 HelloSpring 
我们在这里使用一个很简单的案例去体现上面的概论
**1.在source中创建对应的Spring配置文件**
```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xsi:schemaLocation="http://www.springframework.org/schema/beans
        https://www.springframework.org/schema/beans/spring-beans.xsd">

<!--使用Spring来创建对象，在Spring这些都称为Bean

原来：
Hello hello = new Hello();
类型 变量名 = new 类型

id:变量名
class:要new的对象
property:相当于于给对象的属性设一个值

-->
<bean id="hello" class="com.kuang.pojo.Hello">
    <property name="str" value="Spring"/>
</bean>
</beans>
```
**2.创建一个pojo实体类**

```java
public class Hello {
    private  String str;

    public String getStr() {
        return str;
    }

    public void setStr(String str) {
        this.str = str;
    }

    @Override
    public String toString() {
        return "Hello{" +
                "str='" + str + '\'' +
                '}';
    }
}
```
**3.创建一个测试类**

```java
public class MyTest {
    public static void main(String[] args) {
        //获取Spring的上下文对象
        ApplicationContext context = new ClassPathXmlApplicationContext("beans.xml");
        //我们的对象现在都在Spring中管理了，我们要使用直接去里面取出来了
        //参数对于id
        Hello hello = (Hello)context.getBean("hello");
        System.out.println(hello.toString());
    }}
```
**为什么ClassPathXmlApplicationContext会变成 ApplicationContext？** 
![在这里插入图片描述](https://img-blog.csdnimg.cn/c415c0261ead40b4a991451be31ce333.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAc3BlY2lhbHdpbmU=,size_20,color_FFFFFF,t_70,g_se,x_16)

**4.得到对应结果**
![在这里插入图片描述](https://img-blog.csdnimg.cn/5684cd28d07343ff8b5ec98072672e38.png)
**5.思考问题**
- **Hello 对象是谁创建的?**

 	hello对象是由Spring创建的。
- **Hello对象的属性是怎么设置的?**
	hello对象的属性是由Spring容器设置的，
	这个过程就叫控制反转:
	**控制**:谁来控制对象的创建，传统应用程序的对象是由程序本身控制创建的，使用Spring后，对象是由Spring来创建的．

**反转**:程序本身不创建对象，而变成被动的接收对象.
依赖注入:就是利用set方法来进行注入的.

IOC是一种编程思想，由主动的编程变成被动的接收．

可以通过newClassPathXmlApplicationContext去浏览一下底层源码．

**OK，到了现在，我们彻底不用再程序中去改动了，要实现不同的操作，只需要在xml配置文件中进行修改，所谓的loC,一句话搞定:对象由Spring来创建，管理，装配!**

把我们的思想运用到原先服务

**1. 运用到我们原始的服务中,注意：我们注册的是实体类，这里的配置可以由用户修改，通过ref来解决不同需求问题**

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xsi:schemaLocation="http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd">

    <bean id="Impl" class="com.kuang.dao.UserDaoImpl"/>
    <bean id="MysqlImpl" class="com.kuang.dao.UserDaoMysqlImpl"/>
    <bean id="UserServiceImpl" class="com.kuang.service.UserServiceImpl">
        <property name="userDao" ref="Impl"/>
    </bean>
<!--    ref :引用Spring容器中创建好的对象-->
<!--    vaLue :具体的值,基本数据类型!-->

</beans>
```

**2. Test用户端**

```java
public class MyTest {
    public static void main(String[] args) {
      //获得Spring容器
      ApplicationContext context = new ClassPathXmlApplicationContext("beans.xml");
      //创造业务接口这里的getBean是业务接口的id
        UserServiceImpl userServiceImpl =(UserServiceImpl) context.getBean("UserServiceImpl");
        userServiceImpl.getUser();
    }
}
```
## 2.3 IOC创建对象的方式
1. 使用无参构造创建对象，默认!
2. 假设我们要使用有参构造创建对象。
>在spring配置的beans的xml中进行有参构造的设置
- **下标赋值创建对象**
```xml
<bean id="user" class="com.kuang.pojo.User">
<!--这个index是构造对应类型的位置，因为我们的name在第一个所以对应是0-->
    <constructor-arg index="0" value="陆家写java"/>
</bean>
```
- **通过对应类型创建对象**
>不建议使用，因为我们可能存在两种相同类型的参数因此会造成构造错误的问题
```xml
<bean id="user" class="com.kuang.pojo.User">
<!--基本类型像int那些可用直接在type里面用，而引用类型要进行全称的描述-->
       <constructor-arg type="java.lang.String" value="lujiaxian"/>
</bean>
```
- **通过对应的参数名来设置(重点)**

```xml
<bean id="user" class="com.kuang.pojo.User">
   <constructor-arg name="name" value="lujia"/>
</bean>
```
总结:
在配置文件加载的时候，容器中管理的对象就已经初始化了，用户在服务端的不同时候调取对像的时候，出来的是同一个对象
# 3.Spring的配置
## 3.1 别名

我们的类对应的名字是name，别名对应的alias，设置完这个属性以后，我们可用原来类的名字，也可用用别名sadasdasd
```xml
   <alias name="user" alias="sadasdasd"/>
```
## 3.2 Bean的配置

```xml
    <bean id="user" class="com.kuang.pojo.User" name="user2 u2,u3ju4">
    <property name="name" value="西部开源"/>
    </bean>
```
1. id : bean 的唯一标识符，也就是相当于我们学的对象名
2. class : bean对象所对应的全限定名:包名+类型-
3. name : 也是别名,而且name可以同时取多个别名
## 3.3 import
一般用于团队开发，**我们在团队中通过不同的分工去实现类型，不同的人编写不同的beans**，但是最后的项目是所有人的配置加载在一起才可以，**所以我们使用import在总配置文件中导入其他配置文件，最后只要使用总配置文件即可**。

- 在applicationContext中进行导入
```xml
<import resource="beans0.xml"/>
<import resource="beans1.xml"/>
<import resource="beans2.xml"/>
<import resource="beans3.xml"/>
```

# 4.DI依赖注入
## 4.1 构造器注入
前面已经说过了
## 4.2 Set方式注入（重点）
- 依赖注入：Set注入
- 依赖：bean对象的创建依赖于容器
- 注入：bean对象的属性由容器来注入

[环境搭建]:

**1.复杂类型**

```java
public class Address {
    private String address;

    public String getAddress() {
        return address;
    }

    public void setAddress(String address) {
        this.address = address;
    }
}
```

**2.真实测试对象**
注意还要有对应的get,set方法和toString方法
```java
public class Student {
    private String name;
    private Address address;
    private String[] books;
    private List<String> hobbys;
    private Map<String,String> card;
    private Set<String> games;
    private String wife;
    private Properties info;}
```
**3.beans.xml**

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xsi:schemaLocation="http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd">
<bean id="student" class="com.kuang.pojo.Student">
<!--    第一种普通值注入，value-->
    <property name="name" value="陆家贤"/>
</bean>
</beans>
```
**4.测试类**

```java
public class MyTest {
    public static void main(String[] args) {
        ApplicationContext context = new ClassPathXmlApplicationContext("beans.xml");
        Student student =(Student) context.getBean("student");
        System.out.println(student.getName());
    }
}
```
**5.完善注入信息**

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xsi:schemaLocation="http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd">
    <bean id="address" class="com.kuang.pojo.Address">
        <property name="address" value="沈阳师范大学"/>
    </bean>
    <bean id="student" class="com.kuang.pojo.Student">
        <!--第一种普通值注入，value-->
        <property name="name" value="陆家贤"/>
        <!--第二种Bean注入，ref-->
        <property name="address" ref="address"/>
        <!--第三种数组注入-->
        <property name="books">
            <array>
                <value>红楼梦</value>
                <value>西游记</value>
                <value>三国演绎</value>
            </array>
        </property>
        <!--第四种List注入-->
        <property name="hobbys">
            <list>
                <value>听歌</value>
                <value>敲代码</value>
                <value>看电影</value>
            </list>
        </property>
        <!--第五种Map注入-->
        <property name="card">
            <map>
                <entry key="身份证" value="123456789"/>
                <entry key="银行卡" value="987654321"/>
            </map>
        </property>
        <!--第六种set注入-->
        <property name="games">
            <set>
                <value>LOL</value>
                <value>COC</value>
            </set>
        </property>
        <!--第七种空值null的注入-->
        <property name="wife">
                <null/>
        </property>
        <!--第八种properties注入-->
        <property name="info">
            <props>
                <prop key="学号">19008090</prop>
                <prop key="校号">77211</prop>
                <prop key="地位">985211</prop>
            </props>
        </property>
    </bean>

</beans>
```
>此处输出：Student{name='陆家贤', address=Address{address='沈阳师范大学'}, books=[红楼梦, 西游记, 三国演绎], hobbys=[听歌, 敲代码, 看电影], card={身份证=123456789, 银行卡=987654321}, games=[LOL, COC], wife='null', info={学号=19008090, 校号=77211, 地位=985211}}
## 4.3 其他方式

**1. p命名空间的引入（对应property 注入）**

```xml
<bean id="user" class="com.kuang.pojo.User" p:age="18" p:name="陆家贤"/>
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/c01fc7cb07cc40ca8b3fff7c567bbcc2.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAc3BlY2lhbHdpbmU=,size_20,color_FFFFFF,t_70,g_se,x_16)
可以在直接帮我们定义值，也可ref复杂引用问题。
>记得引入xmlns:p="http://www.springframework.org/schema/p"

**2.c命名空间的引入（对应constructor-arg 注入）**

```xml
<bean id="user2" class="com.kuang.pojo.User" c:name="陆家贤" c:age="18"/>
```
可以在直接帮我们定义值，也可ref复杂引用问题。
>记得引入xmlns:c="http://www.springframework.org/schema/c"

**3.测试类**

```java
@Test
public void test(){
    ApplicationContext context = new ClassPathXmlApplicationContext("userbeans.xml");
    User user = context.getBean("user", User.class);
    System.out.println(user);
}
```
>这里改进了getBean的用法，在参数使用了对应的类，不用再进行强制转换

**4.总结**
我们需要导入约束，同时要求要实体类有对应的有参和无参构造
## 4.4 作用域的实现
bean的作用域一共有六种
![在这里插入图片描述](https://img-blog.csdnimg.cn/c86081768105426bb3f123d7f828f1c2.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAc3BlY2lhbHdpbmU=,size_20,color_FFFFFF,t_70,g_se,x_16)
我们掌握前两个即可
**1. 单例模式**

```xml
<bean id="user2" class="com.kuang.pojo.User" c:name="陆家贤" c:age="18" scope="singleton"/>
```
默认状态下都说单例模式
![在这里插入图片描述](https://img-blog.csdnimg.cn/083229d56b6e4036891d126c76611713.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAc3BlY2lhbHdpbmU=,size_20,color_FFFFFF,t_70,g_se,x_16)


**2. 原型模式**

```xml
<bean id="user2" class="com.kuang.pojo.User" c:name="陆家贤" c:age="18" scope="prototype"/>
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/577dd4c285ca4598878f57e337107292.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAc3BlY2lhbHdpbmU=,size_20,color_FFFFFF,t_70,g_se,x_16)

**3. 测试**

```java
@Test
public void test(){
    ApplicationContext context = new ClassPathXmlApplicationContext("userbeans.xml");
    User user = context.getBean("user", User.class);
    User user2 = context.getBean("user", User.class);
    System.out.println(user==user2);
}
```
**4.总结**
1. 单例模式下我们用户调用的getBean都是同一个对象
2. 原型模型下我们的用户调用的getBean不是同一个对象
3. 其余的request、session、application、这些个只能在web开发中使用到!
# 5.Bean的自动装配
- 自动装配是Spring满足bean依赖一种方式!
- Spring会在上下文中自动寻找，并自动给bean装配属性!

在Spring中有三种装配的方式：
1. 在xml中显示的配置
2. 在java中显示配置
3. 隐式的自动装配bean
## 5.1 环境搭配
**1. 创造三个类即对应的bean装配**

```java
public class Cat {
    public void shoot(){
        System.out.println("喵喵喵");
    }
}
```

```java
public class Dog {
    public void shoot(){
        System.out.println("汪汪汪");
    }
}
```

```java
public class People {
    private Cat cat;
    private Dog dog;
    private String name;

    public People(Cat cat, Dog dog, String name) {
        this.cat = cat;
        this.dog = dog;
        this.name = name;
    }

    public People() {
    }

    @Override
    public String toString() {
        return "People{" +
                "cat=" + cat +
                ", dog=" + dog +
                ", name='" + name + '\'' +
                '}';
    }

    public Cat getCat() {
        return cat;
    }

    public void setCat(Cat cat) {
        this.cat = cat;
    }

    public Dog getDog() {
        return dog;
    }

    public void setDog(Dog dog) {
        this.dog = dog;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }
}
```

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xsi:schemaLocation="http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd">
<bean id="dog" class="com.kuang.pojo.Dog"/>
<bean id="cat" class="com.kuang.pojo.Cat"/>
<bean id="people" class="com.kuang.pojo.People">
    <property name="cat" ref="cat"/>
    <property name="dog" ref="dog"/>
    <property name="name" value="小路小路"/>
</bean>
</beans>
```

**2. 测试类查看测试环境是否正常**

```java
public class MyTest {
    @Test
    public void test(){
        ApplicationContext context = new ClassPathXmlApplicationContext("beans.xml");
        People people = context.getBean("people", People.class);
        people.getDog().shoot();
        people.getCat().shoot();
    }
}
```
## 5.2 byName自动注入

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xsi:schemaLocation="http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd">
<bean id="dog" class="com.kuang.pojo.Dog"/>
<bean id="cat" class="com.kuang.pojo.Cat"/>
<bean id="people" class="com.kuang.pojo.People" autowire="byName">
    <property name="name" value="小路小路"/>
</bean>
</beans>
```
byName:会自动在容器上下文中查找，和自己对象set方法后面的值对应的 beanid。

**注意：这里的容器里面的一定是同一名称才可以进行byName才可以进行识别**
## 5.3 byType自动注入

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xsi:schemaLocation="http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd">
<bean id="dog" class="com.kuang.pojo.Dog"/>
<bean id="cat" class="com.kuang.pojo.Cat"/>
<bean id="people" class="com.kuang.pojo.People" autowire="byType">
    <property name="name" value="小路小路"/>
</bean>
</beans>
```
byName:会自动在容器上下文中查找，和自己对象set方法后的类型对应的 beanid。

**注意：这里的容器里面的一定是只有同一类型才可以进行byName才可以进行识别，要是有两个一样的类型马上报错**

## 5.4 byName and byType小结
- byname的时候，需要保证所有bean的id唯一，并且这个bean需要和自动注入的属性的set方法的值一致!
- bytype的时候，需要保证所有bean的class唯一，并且这个bean需要和自动注入的属性的类型一致

## 5.5 使用注解实现自动装配
jdk1.5支持的注解，Spring2.5就支持注解了!

要使用注解须知:
**1.导入约束:context约束**
**2.配置注解的支持： context:annotation-config/**

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
    xmlns:context="http://www.springframework.org/schema/context"
    xsi:schemaLocation="http://www.springframework.org/schema/beans
        https://www.springframework.org/schema/beans/spring-beans.xsd
        http://www.springframework.org/schema/context
        https://www.springframework.org/schema/context/spring-context.xsd">

    <context:annotation-config/>

</beans>
```
**1. @Nullable**

如果字段标记了这个注解，说明这个字段可以为null。
**2. @Autowired**

直接在属性上使用即可，也可以在set方式上使用。

```java
public @interface Autowired {
    boolean required() default true;
}
```

使用Autowired 我们可以不用编写Set方法了，前提是你这个自动装配的属性在IOC (Spring）容器中存在。


如果显示定义了Autowired 的required属性为false，说明这个对象可以为null，否则不允许为空。


**问题：假如我们有很多个Type但是对应的Name也不一样的时候我们该怎么办？**

```java
@Qualifier(value = "")
```
加上一个对应的注解Value对应IOC里面的id值

**3. @Resource**

是java的注解，这里的@Qualifier对应的是
```java
@Resource(name = "")
```
来代替，但是我们更推荐我们的@Autowired，更加智能

**4. @Resource和@Autowired注解的区别**

1. @Resource和@Autowired注解都是用来实现依赖注入的。
2. **他们判断的先后顺序不一样**
3. @Autowired实际上是**先调用了byType方法**以后，查看在IOC容器中有多少个对应的type类型值，如果有多个的情况下就进行byName。
4. @Resource实际上是**先调用了byName方法**以后，查看在IOC容器中有多少个对应的type类型值，如果有多个的情况下就进行byType。

# 6.Spring的注解开发

1. 在Spring4之后，要使用注解开发，必须要保证aop的包导入了
>我们在导入springMvc的时候自动帮我们导入了
2. 使用注解需要导入context约束，增加注解的支持!|

## 6.1 bean
1. @Component注解引入
```java
@Component
public class User {
    private  String  name="陆家贤";

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }
}
```
当我们使用@Component的时候相当于我们在IOC容器中实体化了这个类的存在。

2. 对应的MyTest类中，我们的id变成了我们对应的类的开头小写的类名

```java
public class MyTest {
    public static void main(String[] args) {
        ApplicationContext context = new ClassPathXmlApplicationContext("beans.xml");
        User user = context.getBean("user", User.class);
        System.out.println(user.getName());
    }
}
```

## 6.2 属性如何注入

既然可以直接对类进行IOC实体化，那类的属性也可以对应的进行赋值

```java
@Component
public class User {
    @Value("陆家贤")
    private  String  name;
}
    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }
}
```
此时我们调用对应的getName方法也可以正确获得对应的值。
>这里我们推荐简单的使用就行

## 6.3 衍生的注解

@Component注解有几个衍生注解，我们在Web开发中，会按照mvc三层架构分层

```java
//dao对应
@Repository
//service对应
@Service
//controller对应
@Controller
```

>我们学习通的项目就是对应的三层架构，当我们的目的是为了扫描三个层的时候，我们需要扫描的地方就是com.kuang

**它们都是@Component的一个组件，代表我们的某个类注册到IOC容器中装配到Bean中**

## 6.4 自动装配置

```java
@Resource
@Autowired
@Nullable
```

## 6.5 作用域

在实体类中，我们之前提过对应注册的作用域的问题。在现在改变对应的配置以后我们使用

```java
@scope("")
```
里面的对应之前作用域的不同领域，包括单例实例等。

## 6.6 小结
**xml与注解:**
- xml更加万能，适用于任何场合，维护简单方便。
- 注解不是自己类使用不了，维护相对复杂

**xml与注解最佳实践：**
- xml用来管理bean
- 注解只负责完成属性的注入
- 最重要的是我们要使用注解时候要配置对应的xml文件
```xml
<context:component-scan base-package="com.kuang.pojo"/>
<context:annotation-config/>
```
# 7.使用Java的方式配置Spring（目前的核心功能）
我们现在要完全不使用Spring的xml配置了，全权交给Java来做，Javaconfig 是Spring的一个子项目，在spring4之后，它成为了一个spring的一个核心功能。

## 7.1 @Configuration

**1. 使用@Configuration时候我们要先明白它的内部结构，我们发现他也是@Component的一部分，即将自己已经注册到IOC容器当中。**

```java
@Target({ElementType.TYPE})
@Retention(RetentionPolicy.RUNTIME)
@Documented
@Component
public @interface Configuration {
    @AliasFor(
        annotation = Component.class
    )
    String value() default "";

    boolean proxyBeanMethods() default true;
}
```
**2. 当我们在某个类标志这个注解时候，我们相当于让这个类的功能等同于我们之前的xml文件，同时将自己也注册到其中**

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xmlns:context="http://www.springframework.org/schema/context"
       xsi:schemaLocation="http://www.springframework.org/schema/beans
        https://www.springframework.org/schema/beans/spring-beans.xsd
        http://www.springframework.org/schema/context
        https://www.springframework.org/schema/context/spring-context.xsd">
    <!--指定我们的需要扫描的包的，包里面的注解就可以用了-->
    <context:component-scan base-package="com.kuang"/>
    <context:annotation-config/>
</beans>
```
**3. 不过此时，我们的测试类的引用也变得不同起来，因为我们的引进从xml文件转换成了class文件**

```cpp
ApplicationContext context = new AnnotationConfigApplicationContext(kuangconfig.class);
```
>这里的kuangconfig.class是我们使用了@Configuration的对象class类。

## 7.2 @Bean注解

这个注解类似于bean xml配置文件中的bean元素，用来在spring容器中注册一个bean。

**1. @Bean注解用在方法上，表示通过方法来定义一个bean，默认将方法名称作为bean名称，将方法返回值作为bean对象，注册到spring容器中。**


```cpp
//注册一个bean ,就相当于我们之前写的一个bean标签
//这个方法的名字,就相当丁bean标签中的id属性
//这个方法的返回值,就相当于bean标签中的cLass属性
@Bean
public User getUser(){
//就是返回到要注入bean的对象,我们在这返回以后，把我们User对象给注入到IOC容器中
    return new User(); 
}
```

**2. 我们注册以对应的bean的id是对应的方法名，所以总的测试方法我们应该是**

```java
public class MyTest {
    public static void main(String[] args) {
ApplicationContext context = new AnnotationConfigApplicationContext(kuangconfig.class);
        User user =(User) context.getBean("getUser");
        System.out.println(user.getName());
    }
}
```
**3. 我们的@bean**

```java
@Target({ElementType.METHOD, ElementType.ANNOTATION_TYPE})
@Retention(RetentionPolicy.RUNTIME)
@Documented
public @interface Bean {
    @AliasFor("name")
    String[] value() default {};

    @AliasFor("value")
    String[] name() default {};

    /** @deprecated */
    @Deprecated
    Autowire autowire() default Autowire.NO;

    boolean autowireCandidate() default true;

    String initMethod() default "";

    String destroyMethod() default "(inferred)";
}
```
我们可以看到，我们可以设置对应的value和name值，其实两个的定义的内容是一样的value和name是一样的，设置的时候，这2个参数只能选一个，原因是@AliasFor导致的

**其中value：字符串数组，第一个值作为bean的名称，其他值作为bean的别名**

## 7.3 @Configuration和@Bean小结
被@Configuration修饰的类，spring容器中会通过cglib给这个类创建一个代理，代理会拦截所有被@Bean修饰的方法。

**默认情况（bean为单例）下确保这些方法只被调用一次，从而确保这些bean是同一个bean，即单例的。如果不添加，则会注册多个bean对象，它们是各不相同的类型。**
>详细可移步到https://cloud.tencent.com/developer/article/1751910

**我们在Springboot随处可见，非常非常非常重要**
# 8.代理模式
为什么要学习代理模式?因为这就是SpringAOP的底层(SpringAOP和SpringMVC)

代理模式的分类:
- 静态代理
- 动态代理

## 8.1 静态代理
![在这里插入图片描述](https://img-blog.csdnimg.cn/4c0f1d033aa745c197b1ebace589e871.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAc3BlY2lhbHdpbmU=,size_20,color_FFFFFF,t_70,g_se,x_16)
角色分析：
- 抽象角色：一般使用接口或者抽象类来处理
- 真实角色：被代理的决定
- 代理角色：代理真实角色后我们一般做附属操作
- 客户：访问代理对象的人

代码步骤:

1.接口

```java
public interface Rent {
    public void rent();
}
```

⒉真实角色
```java
public class Host implements Rent{
public void rent(){
    System.out.println("出租房屋");
}
}
```

3.代理角色

```java
public class Proxy implements Rent{
    private Host host;

    public Proxy() {
    }

    public Proxy(Host host) {
        this.host = host;
    }
    public void rent(){
        seeHouse();
        host.rent();
        fare();
        hetong();
    }
    public void seeHouse(){
        System.out.println("中介带你看房");
    }
    public void fare(){
        System.out.println("中介费");
    }
    public void hetong(){
        System.out.println("签个合同");
    }
}
```

4.客户端访问代理角色


```java
public class Client {
    public static void main(String[] args) {
        Host host = new Host();
        Proxy proxy = new Proxy(host);
        proxy.rent();
    }
}
```




**代理模式的好处:**
- 可以使真实角色的操作更加纯粹!不用去关注一些公共的业务
- 公共也就就交给代理角色，实现了业务的分工
- 公共业务发生扩展的时候，方便集中管理

**缺点:**
- —个真实角色就会产生一个代理角色；代码量会翻倍



## 8.2 加深理解

当我们需要增添新功能的时候，我们要是dao层进行代码的修改，有可能会导致前端输出的逻辑出现偏差，导致整个系统的崩坏，为了解决这个问题，我们现在进行了代理的服务。

代码步骤:

1.接口

```java
public interface UserService {
    public void add();
    public void delete();
    public void update();
    public void select();
}
```
⒉真实角色(需要被代理的对象，即对应的Dao的底层逻辑层

```java
//真实对象
public class UserServiceImpl implements UserService{

    @Override
    public void add() {
        System.out.println("增加用户");
    }

    @Override
    public void delete() {
        System.out.println("删除一个用户");
    }

    @Override
    public void update() {
        System.out.println("更新一个用户");
    }

    @Override
    public void select() {
        System.out.println("查找一个用户");
    }
    //改变原有的代码在公司中是大忌
}

```
3.代理角色（我们要求我们需要在执行每个方法前进行输出执行方法的提示）

```java
public class UserServiceProxy implements UserService{
    private UserServiceImpl userService;

    public void setUserService(UserServiceImpl userService) {
        this.userService = userService;
    }

    @Override
    public void add() {
        log("add");
        userService.add();
    }

    @Override
    public void delete() {
        log("delete");
        userService.delete();
    }

    @Override
    public void update() {
        log("update");
        userService.update();
    }

    @Override
    public void select() {
        log("select");
        userService.select();
    }
    public void log(String msg){
        System.out.println("使用了" + msg + "方法");
    }
}
```

4.此时的用户层

```java
public class Client {
    public static void main(String[] args) {
    //导入我们需要的服务端
        UserServiceImpl userService = new UserServiceImpl();
	//导入代理端
        UserServiceProxy proxy = new UserServiceProxy();
    //进入该服务的代理段 
        proxy.setUserService(userService);
	
        proxy.add();


    }
}
```

此时我们的可以执行原逻辑代码的情况下同时增添新功能。

## 8.3 动态代理
 - 动态代理和静态代理角色一样
 - 动态代理的代理类是动态生成的，不是我们直接写好的!
 - 动态代理分为两大类：基于接口的动态代理，基于类的动态代理
	 - 基于接口---JDK动态代理
      - 基于类: cglib
      -  iava字节码实现: javasist
	   需要了解两个类: 
- Proxy: 代理
- InvocationHandler: 调用处理程序

我们用要生成自动代理的类，我们要继承InvocationHandler，获得invoke的方法是重写，为了处理代理实例并返回结果。

记住`public Object getProxy(){return Proxy.newProxyInstance(this.getClass().getClassLoader(),rent.getClass().getInterfaces(),this);`这是一个固定写法，我们用它来返回pr


**1.静态代理我们的类rent**
```java
//等我们会用这个类，自动生成代理类
public class ProxyInvocationHandler implements InvocationHandler {
//被代理的接口
    private Rent rent;

    public void setRent(Rent rent){
        this.rent=rent;
    }
//生成得到代理类
    public Object getProxy(){
        return  Proxy.newProxyInstance(this.getClass().getClassLoader(),rent.getClass().getInterfaces(),this);

    }
    //处理代理实例并返回结果
    @Override
    public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
        //动态代理的本质就是利用反射机制实现
        seeHouse();
        Object result = method.invoke(rent, args);
        fare();
        return result;
    }
    public void seeHouse(){
        System.out.println("中介带看房子");
    }
    public void fare(){
        System.out.println("收中介费");
    }
}
```
由用户端来产生动态代理机制代码
```java
public class Client {
    public static void main(String[] args) {
        //真实角色
        Host host = new Host();

        //代理角色：现在没有
        ProxyInvocationHandler pih = new ProxyInvocationHandler();
        //通过调用程序处理我们要调用的接口对象
        pih.setRent(host);
        Rent proxy = (Rent) pih.getProxy();
        proxy.rent();

    }
}
```
**2.动态使用代理**

```java

//等我们会用这个类，自动生成代理类
public class ProxyInvocationHandler implements InvocationHandler {
	//被代理的接口
    private Object target;

    public void settarget(Object target){
        this.target=target;
    }

	//生成得到代理类
    public Object getProxy(){
        return  Proxy.newProxyInstance(this.getClass().getClassLoader(),target.getClass().getInterfaces(),this);

    }

    //处理代理实例并返回结果
    @Override
    public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
        //动态代理的本质就是利用反射机制实现
        seeHouse();
        //反射全自动
        log(method.getName());
        Object result = method.invoke(target, args);
        fare();
        return result;
    }
    public void seeHouse(){
        System.out.println("中介带看房子");
    }
    public void fare(){
        System.out.println("收中介费");
    }
    public void  log(String msg){
        System.out.println("执行了" + msg + "方法");
    }

```

```cpp

public class Client {
    public static void main(String[] args) {
        //真实角色
        UserServiceImpl userService = new UserServiceImpl();
        //代理对象不存在
        ProxyInvocationHandler pih = new ProxyInvocationHandler();
        //设置要代理的对象
        pih.settarget(userService);
        //动态生成代理类
        UserService proxy = (UserService) pih.getProxy();
        proxy.add();
    }
}
```
# 9.AOP
## 9.1 什么是AOP
AOP (Aspect Oriented Programming)意为**面向切面编程，通过预编译方式和运行期动态代理实现程序功能的统一维护的一种技术**。

AOP是OOP的延续,是软件开发中的一个热点，也是Spring框架中的一个重要内容,是函数式编程的一种衍生范型。利用AOP可以对业务逻辑的各个部分进行隔离，从而使得业务逻辑各部分之间的耦合度降低，提高程序的可重用性，同时提高了开发的效率。
## 9.2 Aop在Spring中的作用
**提供声明式事务：允许用户自定义切面**
- 横切关注点:跨越应用程序多个模块的方法或功能。即是，与我们业务逻辑无关的，但是我们需要关注的部分，就是横切关注点。如日志,安全,缓存,事务等等
>就是日志
- 切面(ASPECT) :横切关注点被模块化的特殊对象。即，它是一个类。
>就是log类
- 通知(Advice) :切面必须要完成的工作。即，它是类中的一个方法。
>就是log的方法
- 目标(Target) :被通知对象。
- 代理(Proxy) :向目标对象应用通知之后创建的对象。
- 切入点(PointCut) :切面通知执行的“地点”的定义。
- 连接点(JointPoint) :与切入点匹配的执行点。

SpringAOP中，通过Advice定义横切逻辑，Spring中支持5种类型的Advice:

![在这里插入图片描述](https://img-blog.csdnimg.cn/c9bc62e98f6f42e19e13d509fd89ae0b.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAc3BlY2lhbHdpbmU=,size_20,color_FFFFFF,t_70,g_se,x_16)
## 9.3 使用Spring实现AOP
**1. 使用AOP织入，需要导入一个依赖包并编写测试类且更新标签库**

```xml
    <dependency>
         <groupId>org.aspectj</groupId>
         <artifactId>aspectjweaver</artifactId>
         <version>1.9.4</version>
     </dependency>
```

```java
public class MyTest {
    public static void main(String[] args) {
        ApplicationContext context = new ClassPathXmlApplicationContext("beans.xml");
        UserService userService = (UserService)context.getBean("userService");
        userService.add();
    }
}
```

```cpp
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xmlns:aop="http://www.springframework.org/schema/aop"
       xsi:schemaLocation="http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd
                                http://www.springframework.org/schema/aop http://www.springframework.org/schema/aop/spring-aop.xsd">
 </beans>
```

**2. 方式一：使用Spring的API接口**

```java
public class Afterlog implements AfterReturningAdvice {
    @Override
    //returnValue
    public void afterReturning(Object returnValue, Method method, Object[] args, Object target) throws Throwable {
        System.out.println("执行了" + method.getName() + "方法，返回结果为：" + returnValue);
    }
}
```

```java
public class log implements MethodBeforeAdvice {
//method:要执 行的目标对象的方法
//args:参数
//target:目标对象
    @Override
    public void before(Method method, Object[] objects, Object target) throws Throwable {
        System.out.println(target.getClass().getName() + "的" + method.getName() + "被执行了");
    }
}

```

```xml
<!--    方法一使用原生的Spring API接口-->
<!--    配置aop:需要导入aop约束-->
    <aop:config>
<!--        切入点:expression:表达式,execution(要执行的位置)-->
<!--        *代表任意返回类型-->
<!--        com.kuang.service.UserServiceImpl.*是UserServiceImpl的方法-->
<!--        后面的(..)的是说明说明方法的()的参数的是任意类型-->
        <aop:pointcut id="pointcut" expression="execution(* com.kuang.service.UserServiceImpl.*(..))"/>

<!--        执行环绕增加,即把log这个类插入到pointcut方法中-->
        <aop:advisor advice-ref="log" pointcut-ref="pointcut"/>
        <aop:advisor advice-ref="afterLog" pointcut-ref="pointcut"/>
    </aop:config>
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/cbe6f63deec043b5a9795b0066d86a07.png)


**3.方式二：使用我们的自定义类去实现**

```cpp
public class DiyPointCut {
    public void before(){
        System.out.println("========方法执行前============");
    }
    public void after(){
        System.out.println("=========方法执行后========");
    }
}

```

```xml
    <bean id="diy" class="com.kuang.diy.DiyPointCut"/>
    <aop:config>
<!--        自定义切面，ref要引用的类-->
        <aop:aspect ref="diy">
<!--            切入点-->
            <aop:pointcut id="point" expression="execution(* com.kuang.service.UserServiceImpl.*(..))"/>
<!--            通知-->
            <aop:before method="before" pointcut-ref="point"/>
            <aop:after method="after" pointcut-ref="point"/>
        </aop:aspect>
    </aop:config>
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/585e47e890c94d9e9199c0eeb4d5e8ae.png)


**4.方式三：用注解实现**

```cpp
    <bean id="annotationPointCut " class="com.kuang.diy.AnnotationPointCut"/>
<!--    开启注解支持-->
    <aop:aspectj-autoproxy/>
```

```cpp
@Aspect//标注这个类是一个切面
public class AnnotationPointCut {
    @Before("execution(* com.kuang.service.UserServiceImpl.*(..))")
    public void before(){
        System.out.println("========方法执行前========");
    }
    @After("execution(* com.kuang.service.UserServiceImpl.*(..))")
    public void after(){
        System.out.println("========方法执行后========");
    }
    @Around("execution(* com.kuang.service.UserServiceImpl.*(..))")
    public void around(ProceedingJoinPoint jp) throws Throwable {
        System.out.println("环绕前");

//        Signature signature = jp.getSignature();
//        System.out.println("signature"+signature);
        //执行方法
        Object proceed = jp.proceed();

        //环绕后
        System.out.println("环绕后");
//        System.out.println(proceed);
    }
}
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/9d747dafcd9648cfb0bf657c6f1b40da.png)
# 10.整合Mybatis

## 10.1.整合两个框架首先导入相关jar包

```xml
    <dependencies>
        <dependency>
            <groupId>junit</groupId>
            <artifactId>junit</artifactId>
            <version>4.12</version>
            <scope>test</scope>
        </dependency>
        <dependency>
            <groupId>mysql</groupId>
            <artifactId>mysql-connector-java</artifactId>
            <version>8.0.25</version>
        </dependency>
        <dependency>
            <groupId>org.mybatis</groupId>
            <artifactId>mybatis</artifactId>
            <version>3.5.7</version>
        </dependency>
        <dependency>
            <groupId>org.springframework</groupId>
            <artifactId>spring-webmvc</artifactId>
            <version>5.2.12.RELEASE</version>
        </dependency>
        <dependency>
            <groupId>org.springframework</groupId>
            <artifactId>spring-jdbc</artifactId>
            <version>5.3.9</version>
        </dependency>
        <dependency>
            <groupId>org.aspectj</groupId>
            <artifactId>aspectjweaver</artifactId>
            <version>1.9.4</version>
        </dependency>
        <dependency>
            <groupId>org.mybatis</groupId>
            <artifactId>mybatis-spring</artifactId>
            <version>2.0.6</version>
        </dependency>
    </dependencies>
```
## 10.2 编写mybayis的配置文件

```xml
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE configuration
  PUBLIC "-//mybatis.org//DTD Config 3.0//EN"
  "http://mybatis.org/dtd/mybatis-3-config.dtd">
<configuration>
  <environments default="development">
    <environment id="development">
      <transactionManager type="JDBC"/>
      <dataSource type="POOLED">
        <property name="driver" value="${driver}"/>
        <property name="url" value="${url}"/>
        <property name="username" value="${username}"/>
        <property name="password" value="${password}"/>
      </dataSource>
    </environment>
  </environments>
  <mappers>
    <mapper resource="org/mybatis/example/BlogMapper.xml"/>
  </mappers>
</configuration>
```
>负责配置Mybatis环境，其中设置环境id为development，对应的transactionManager为JDBC，而dataSource是pooled类型的的数据库连接

## 10.3 配置对应的Spring核心配置xml，用spring托管我们的mybatis

**1.SqlSession**

在 MyBatis 中，你可以使用 `SqlSessionFactory` 来创建 `SqlSession`。 一旦你获得一个 `session` 之后，你可以使用它来执行映射了的语句，提交或回滚连接，最后，当不再需要它的时候，你可以关闭 `session`。 

使用 MyBatis-Spring 之后，你不再需要直接使用 `SqlSessionFactory` 了，因为你的 `bean` 可以被注入一个线程安全的 `SqlSession`，它能基于 Spring 的事务配置来自动提交、回滚、关闭 `session`。

**2.SqlSessionTemplate**

`SqlSessionTemplate` 是 MyBatis-Spring 的核心。作为 `SqlSession` 的一个实现，这意味着可以使用它无缝代替你代码中已经在使用的 `SqlSession`。 `SqlSessionTemplate` 是线程安全的，可以被多个 `DAO` 或映射器所共享使用。

当调用 SQL 方法时（包括由 `getMapper()` 方法返回的映射器中的方法），`SqlSessionTemplate` 将会保证使用的 `SqlSession` 与当前 Spring 的事务相关。 此外，它管理 `session` 的生命周期，包含必要的关闭、提交或回滚操作。另外，它也负责将 MyBatis 的异常翻译成 Spring 中的 `DataAccessExceptions`。

由于模板可以参与到 Spring 的事务管理中，并且由于其是线程安全的，可以供多个映射器类使用，你应该总是用 `SqlSessionTemplate` 来替换 MyBatis 默认的 `DefaultSqlSession` 实现。在同一应用程序中的不同类之间混杂使用可能会引起数据一致性的问题。

**可以使用 `SqlSessionFactory` 作为构造方法的参数来创建 `SqlSessionTemplate` 对象。**
```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xmlns:aop="http://www.springframework.org/schema/aop"
       xsi:schemaLocation="http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd
                                http://www.springframework.org/schema/aop http://www.springframework.org/schema/aop/spring-aop.xsd">

    <!--DataSource:使用Spring的数据源替换Mybatis的配置c3p0 dbcp druid
    我们用Spring提供的jdbc DriverManagerDataSource
    -->
    <bean id="dataource" class="org.springframework.jdbc.datasource.DriverManagerDataSource">
        <property name="driverClassName" value="com.mysql.cj.jdbc.Driver"/>
        <property name="url" value="jdbc:mysql://localhost:3306/mybatis?useSSL=true&amp;useUnicode=true&amp;characterEncoding=UTF-8"/>
        <property name="username" value="root"/>
        <property name="password" value="123456"/>
    </bean>

    <!--sqlSessionFactory-->
    <bean id="sqlSessionFactory" class="org.mybatis.spring.SqlSessionFactoryBean">
        <property name="dataSource" ref="dataSource" />
<!-- 要绑定Mybatis配置文件，我们把mybatis和spring整合也要告诉我们的mybatis核心配置文件的位置-->
        <property name="configLocation" value="classpath:mybatis-config.xml"/>
<!--注册映射器，就是等下对应的*mapper.xml文件-->
        <property name="mapperLocations" value="classpath:com/kuang/mapper/*.xml"/>
    </bean>
<!--SqlSessionTemplate就是sqlSession-->
    <bean id="sqlSession" class="org.mybatis.spring.SqlSessionTemplate">
<!--只能用构造器注入sqlSessionFactory 因为他没有Set方法-->
        <constructor-arg index="0" ref="sqlSessionFactory"/>
    </bean>

</beans>
```
从此我们的Mybatis变得简单起来

```xml
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE configuration
        PUBLIC "-//mybatis.org//DTD Config 3.0//EN"
        "http://mybatis.org/dtd/mybatis-3-config.dtd">
<!--核心配置文件-->
<configuration>
    <!--环境-->
    <typeAliases>
        <package name="com.kuang.pojo"/>
    </typeAliases>

<!--    <settings>-->
<!--        <setting name="" value=""/>-->
<!--    </settings>-->
</configuration>
```
**一般情况下我们只在mybatis留下两个东西一个是别名管理一个是setting**

现在，这个 bean 就可以直接注入到你的 `DAO/Mapper `bean 中了。你需要在你的 bean 中添加一个 `SqlSession` 属性，就像下面这样：


1. 不继承使用接口
```java
public class UserMapperImpl implements UserMapper{

    //我们的所有操作都使用sqlSession来执行，现在都使用SqlSessionTemplate
    private SqlSessionTemplate sqlSession;

    public void setSqlSession(SqlSessionTemplate sqlSession) {
        this.sqlSession = sqlSession;
    }

    @Override
    public List<User> selectUser() {
        UserMapper mapper = sqlSession.getMapper(UserMapper.class);
        return  mapper.selectUser();
    }
}
```
2. 继承使用接口

```java
public class UserMapperImpl extends SqlSessionDaoSupport implements UserMapper{
    @Override
    public List<User> selectUser() {
    //这里的sqlSession变成了是getSqlSession()获取的
        UserMapper mapper = getSqlSession().getMapper(UserMapper.class);
        return  mapper.selectUser();
    }
}
```

# 11.声明式事务
## 11.1 回顾事务
- 要么都成功，要么都失败! .
- 事务在项目开发中，十分的重要，涉及到数据的一致性问题，不能马虎
- 确保完整性和一致性;

事务ACID原则:
- 原子性
- 一致性
- 隔离性
>多个业务操作同一个资源，防止数据损坏
- 持久性
>事务一旦提交，无论系统发生什么问题，结果都不会被影响，被持久化写到存储器当中
## 11.2 spring中的事务管理
- 声明式事务: AOP
- 编程式事务:需要再代码中,进行事务的管理
## 11.3 为什么需要事务
为什么需要事务?
1. 如果不配置事务，可能存在数据提交不-致的情况下;
2. 如果我们不在SPRING中去配置声明式事务,我们就需要在代码中手动配置事务!
3. 事务在项目的开发中十分重要，设计到数据的-致性和完整性问题，不容马虎!

## 11.4 事务的传递问题
我们在整合框架中，如果我们不配置我们的事务，**在一个方法中多多个方法，其中一个方法是执行错误的情况下，继续执行后面的方法，导致我们的一个方法中部分方法执行成功，部分方法执行失败**。

为了避免这个情况的出现，我们需要在Spring配置是事务管理。在整个框架中我们借助了 Spring 中的 `DataSourceTransactionManager` 来实现事务管理。一旦配置好了 Spring 的事务管理器，你就可以在 Spring 中按你平时的方式来配置事务。并且支持 `@Transactional` 注解和 AOP 风格的配置。在事务处理期间，一个单独的 `SqlSession` 对象将会被创建和使用。当事务完成时，这个 `session` 会以合适的方式提交或回滚。


**1. 标准配置**
要开启 Spring 的事务处理功能，在 Spring 的配置文件中创建一个 `DataSourceTransactionManager` 对象：

```xml
<bean id="transactionManager" class="org.springframework.jdbc.datasource.DataSourceTransactionManager">
  <property name="dataSource" ref="dataSource" />
</bean>
```
**2.我们推荐使用 AOP 实现事务的织入**

```xml
<!--配置事务通知-->
    <tx:advice id="txAdvice" transaction-manager="transactionManager">
<!--        给方法配置事务-->
<!--        配置事务的传播特性，propagation="REQUIRED"是默认的，propagation是传播-->
        <tx:attributes>
            <tx:method name="*" propagation="REQUIRED"/>
        </tx:attributes>
    </tx:advice>
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/c0ed80916fb94d43a7fa829b7f2649fa.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAc3BlY2lhbHdpbmU=,size_20,color_FFFFFF,t_70,g_se,x_16)
>我们记住第一种和最后一种并明白自己有七种就好

**3.配置事务的切入**

```xml
    <aop:config>
        <aop:pointcut id="txPointCut" expression="execution(* com.kuang.mapper.*.*(..))"/>
        <aop:advisor advice-ref="txAdvice" pointcut-ref="txPointCut"/>
    </aop:config>
```
即我们这个`pointcut`执行制定域的所有方法都会被加上这个事务

设置凡是`mapper/dao`下面所有关于数据库的操作的方法全部加上事务防止我们的执行出现分支
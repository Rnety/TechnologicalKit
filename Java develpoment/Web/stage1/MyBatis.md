# 1.什么是 MyBatis？
- MyBatis 是一款优秀的**持久层框架**。
- 它支持自定义 SQL、存储过程以及高级映射。
- MyBatis 免除了几乎所有的 JDBC 代码以及设置参数和获取结果集的工作。
- MyBatis 可以通过简单的 XML 或注解来配置和映射原始类型、接口和 Java POJO（Plain Old Java Objects，普通老式 Java 对象）为数据库中的记录。
# 2.持久化
## 2.1 数据持久化
- 持久化就是将程序的数据在持久状态和瞬时状态转化的过程
- 内存:**断电即失**
## 2.2 为什么需要持久化
- 有一些对象，不能让他丢掉。
- 内存太贵
## 2.3 持久层
Dao层，Service层，Controller层.....
- 完成持久化工作
- 层界限明显
# 3.为什么需要mybatis
- 方便
- 传统JDBC复杂，是一个简化的框架
- 帮助操作人员把数据存入数据库
- 不用Mybatis也可以，但是容易上手。技术没有高低之分
- 优点:
	- 简单易学
	- 灵活
    - sql和代码的分离，提高了可维护性。
    - 提供映射标签，支持对象与数据库的orm字段关系映射。
    - 提供对象关系映射标签，支持对象关系组建维护。
    - 提供xml标签，支持编写动态sql。
# 4.第一个Mybatis程序

**1.创建数据库**

```sql
create table `use` //这里的use对应了数据库命令，我们如果需要使用这个名称需要使用``号把它特别注释
( id int(20) not null,
name varchar(30) default null,
pwd varchar(30) default null,
primary key(id));
```

```sql
INSERT into `use`(id,name,pwd) VALUES
(1,'狂神','123456'),
(2,'张三','123456'),
(3,'李四','123456');

```
![在这里插入图片描述](https://img-blog.csdnimg.cn/a6358449e3784866bb3300fe7978c8aa.png)
 **2.创建一个Maven**
创造对应依赖**junit，org.mybatis，mysql**

```xml
  <dependencies>
    <dependency>
      <groupId>junit</groupId>
      <artifactId>junit</artifactId>
      <version>4.11</version>
      <scope>test</scope>
    </dependency>
    <dependency>
      <groupId>org.mybatis</groupId>
      <artifactId>mybatis</artifactId>
      <version>3.5.7</version>
    </dependency>
    <dependency>
      <groupId>mysql</groupId>
      <artifactId>mysql-connector-java</artifactId>
      <version>8.0.25</version>
    </dependency>
  </dependencies>
```
**创造项目子mouble**
**1. 在其中resource引进mybatis的xml文件，然后在XML中构建SqlSessionFactory**

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
根据实际改进代码
```xml
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE configuration
        PUBLIC "-//mybatis.org//DTD Config 3.0//EN"
        "http://mybatis.org/dtd/mybatis-3-config.dtd">
<!--核心配置文件-->
<configuration>
<!--环境-->
    <environments default="development">
        <environment id="development">
            <transactionManager type="JDBC"/>
            <dataSource type="POOLED">
                <!-- 驱动-->
                <property name="driver" value="com.mysql.jdbc.Driver"/>
                <property name="url" value="jdbc:mysql://localhost:3306/mybatis?useSSL=true&amp;useUnicode=true&amp;characterEncoding=UTF-8"/>
                <property name="username" value="root"/>
                <property name="password" value="123456"/>
            </dataSource>
        </environment>
    </environments>

</configuration>
```
**2. 编写mybatis工具类**
每个基于 MyBatis 的应用都是以一个 SqlSessionFactory 的实例为核心的。SqlSessionFactory 的实例可以通过 SqlSessionFactoryBuilder 获得。而 SqlSessionFactoryBuilder 则可以从 XML 配置文件或一个预先配置的 Configuration 实例来构建出 SqlSessionFactory 实例。

```java
package com.dao.untils;

import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;

import java.io.IOException;
import java.io.InputStream;

//sqlSessionFactory --> sqlSession
public class MybatisUtils {
    private static SqlSessionFactory sqlSessionFactory;
    static {
    try {
        //获取sqlSessionFactory
        String resource = "org/mybatis/example/mybatis-config.xml";
        InputStream inputStream = Resources.getResourceAsStream(resource);
        SqlSessionFactory sqlSessionFactory = new SqlSessionFactoryBuilder().build(inputStream);
    }catch (IOException e){
        e.printStackTrace();
    }
    }
    //既然有了 SqlSessionFactory，顾名思义，我们就可以从中获得 SqlSession 的实例了。
    // SqLSession完全包含了面向数据库执行SQL命令所需的所有方法。

    public static SqlSession getSqlSessionFactory(){
        return  sqlSessionFactory.openSession();
    }
}

```

 **4.编写代码**
- Dao接口
```java
public interface UserDao {
   List<User> getUseList();
}
```

- 接口实现类由原来的UserDaoImpl转换成一个Mapper配置文件
```xml
<mapper namespace="com.kuang.dao.UserDao">
<!--查询，id对应我们的方法，名字-->
<select id="getUseList" resultType="com.kuang.pojo.User">
    select * from mybatis.user
</select>
</mapper>
```
 **5.测试**
1. 创建Test测试类

```java
public class UserDaoTest {
    @Test
    public void test(){
        //获得sqlSession对象
        SqlSession sqlSession = MybatisUtils.getSqlSession();
        //执行SQL
        //为了拿到UseDao里面的方法，通过这个接口的class对象
        UserDao mapper = sqlSession.getMapper(UserDao.class);
        List<User> useList = mapper.getUseList();


        for (User user :useList) {
        System.out.println(user);
    }
        //关闭sqlSession
        sqlSession.close();
}
}
```
**常见错误**

```cpp
org.apache.ibatis.binding.BindingException: Type interface com.kuang.dao.UserDao is not known to the MapperRegistry.
```
**因为每一个Mapper.xml都需要在Mybatis核心配置文件中注册！**

```xml
<mappers>
    <mapper resource="com/kuang/dao/UserMapper.xml"/>
</mappers>
```
**资源导出失败的问题**
```xml
  <!--在build中配置resources，来防止我们资源导出失败的问题-->
    <build>
        <resources>
            <resource>
                <directory>src/main/resources</directory>
                <includes>
                    <include>**/*.properties</include>
                    <include>**/*.xml</include>
                </includes>
                <filtering>true</filtering>
            </resource>
            <resource>
                <directory>src/main/java</directory>
                <includes>
                    <include>**/*.properties</include>
                    <include>**/*.xml</include>
                </includes>
                <filtering>true</filtering>
            </resource>
        </resources>
    </build>
```
 **6.流程图**
![在这里插入图片描述](https://img-blog.csdnimg.cn/6c5abdbde475422b8ca3735bf5bffc9c.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAc3BlY2lhbHdpbmU=,size_20,color_FFFFFF,t_70,g_se,x_16)
# 5.CRUD
## 5.1 namespace
namespace中的包名要和Dao/mapper接口的包名一致!
## 5.2 select
选择，查询语句
- **id**：对应的namespace中的方法名
- **resultType(类型)**：Sql语句执行的返回值
- **resultMap(集合)**：Sql语句执行的返回集合
- **parameterType**：Sql语句执行时候放进去的参数类型

1.编写接口
2.编写对应的sql语句
3.测试

```java
   User getUserById(int id); //接口类编写
```

```xml
<select id="getUserById" parameterType="int" resultType="com.kuang.pojo.User">
    select * from  mybatis.user where id = #{id};
</select>
```

```bash
    @Test
    public void getUserById(){
        SqlSession sqlSession = MybatisUtils.getSqlSession();
        UserDao mapper = sqlSession.getMapper(UserDao.class);
        User user = mapper.getUserById(1);
        System.out.println(user);
        sqlSession.close();
    }
```

## 5.3 Insert

```java
   int  addUser(User user);//接口类编写
```

```xml
<insert id="addUser" parameterType="com.kuang.pojo.User">
    insert into mybatis.user(id,name,pwd) value(#{id},#{name},#{pwd});
</insert>
```

```cpp
    @Test
    public void addUser(){
        SqlSession sqlSession = MybatisUtils.getSqlSession();
        UserDao mapper = sqlSession.getMapper(UserDao.class);
        int apper = mapper.addUser(new User(4, "哈哈", "123456"));
        if(apper>0)
        {
            System.out.println("输入成功");
        }

        sqlSession.commit();
        sqlSession.close();
    }
```

## 5.4 updata

```java
   int  updateUser(User user);//接口类编写
```

```xml
<update id="updateUser" parameterType="com.kuang.pojo.User">
    update mybatis.user set name=#{name},pwd=#{pwd} where id = #{id}
</update>  
```

```cpp
    @Test
    public void updateUser(){
        SqlSession sqlSession = MybatisUtils.getSqlSession();
        UserDao mapper = sqlSession.getMapper(UserDao.class);
        int apper = mapper.updateUser(new User(4, "呵呵", "123456"));
        if(apper>0){
            System.out.println("更新成功");
        }
        sqlSession.commit();
        sqlSession.close();
    }
```

## 5.5 delete

```java
   int  deleteUser(int id);//接口类编写
```

```xml
<delete id="deleteUser" parameterType="com.kuang.pojo.User">
   delete from mybatis.user where id=#{id}
</delete>
```

```cpp
    @Test
    public void deleteUser(){
        SqlSession sqlSession = MybatisUtils.getSqlSession();
        UserDao mapper = sqlSession.getMapper(UserDao.class);
        int i = mapper.deleteUser(2);
        if(i>0){
            System.out.println("删除成功");
        }
        sqlSession.commit();
        sqlSession.close();
    }
```
## 5.6 模糊查询
**方法一：Java代码执行的时候，传递通配符%%**

```xml
<select id="getUserLike" resultType="com.kuang.pojo.User">
	select * from mybatis.user where name like #{value}
</select>
```

```java
public void getUserLike(){
sqlsession sqlsession = Mybatisutils.getsqlSession();
UserMapper mapper = sqlsession.getMapper(UserMapper.class);
List<user> userList = mapper.getUserLike( value:"%李%");
for (User user : userList) {
System.out.println(user);
}
sqlsession.close();
}
```
**方法二：在sql拼接中使用通配符**
```xml
<select id="getUserLike" resultType="com.kuang.pojo.User">
    select * from mybatis.user where name like "%"${value}"%"
</select>
```
```java
public void getUserLike(){
sqlsession sqlsession = Mybatisutils.getsqlSession();
UserMapper mapper = sqlsession.getMapper(UserMapper.class);
List<user> userList = mapper.getUserLike( value:"李");
for (User user : userList) {
System.out.println(user);
}
sqlsession.close();
}
```
# 6.万能的Map方法
## 6.1 什么是Map以及Map方法
>版权声明：本文在介绍什么是Map以及Map方法中，引入了为CSDN博主「taraex」的原创文章，该文章地址为https://blog.csdn.net/taraex/article/details/90243965，原答主的介绍更加详细，这里只作为学习mybatis的一个插件小介绍
>
>**1. Map集合概述和特点**
>将键映射到值的对象，一个映射不能包含重复的键，每个键最多只能映射到一个值，即**映射和键是一一对应的。**
>**2. Map接口和Collection接口的区别**
>Map接口和Collection接口的不同，Map是双列的,Collection是单列的，Map的键唯一,Collection的子体系Set是唯一的，Map集合的数据结构针对键有效，跟值无关;Collection集合的数据结构是针对元素有效。

**3. Map的方法使用**
![在这里插入图片描述](https://img-blog.csdnimg.cn/a1fc31b7da5c4946b06bdf54fb492592.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAc3BlY2lhbHdpbmU=,size_20,color_FFFFFF,t_70,g_se,x_16)

```java
//1. 添加功能,添加元素。这个其实还有另一个功能即替换,如果键是第一次存储，就直接存储元素，返回null,所以在第一次返回的时候可以不用设置返回值。如果键不是第一次存在，就用值把以前的值替换掉，返回以前的值。
Object put(String key,Object value);

//2. 删除功能，移除所有的键值对元素
void clear();

//3.根据键删除键值对元素，并把值返回
Object remove(String key,Object value);

//4.判断
boolean containsKey(Object key);//判断集合是否包含指定的键
boolean containsValue(Object value);//判断集合是否包含指定的值
boolean isEmpty();//判断集合是否为空


//5.获取功能
Set<Map.Entry<K,V>> entrySet(): 返回一个键值对的Set集合
V get(Object key):根据键获取值
Set keySet():获取集合中所有键的集合
Collection values():获取集合中所有值的集合


//6.长度功能
int size()：返回集合中的键值对的对数
```

**4. 在开发中使用Map方法**
假设，我们的实体类，或者数据库中的表，字段或者参数过多，我们应当考虑使用Map。

```java
  User addUser2(Map<String,Object> map);
```

```java
    @Test
    public void addUser2(){
        SqlSession sqlSession = MybatisUtils.getSqlSession();
        UserDao mapper = sqlSession.getMapper(UserDao.class);


        Map<String, Object> map = new HashMap<String, Object>();

        map.put("userid",5);
        map.put("password","2333333");

        mapper.addUser2(map);

        sqlSession.close();
    }
```

```xml
    <insert id="addUser2" parameterType="map">
        insert into mybatis.user(id,pwd) value(#{useid},#{password});
    </insert>
```
Map传递参数，直接在sql中取出key即可

对象传递参数，直接在sql中取对象的属性即可

只有一个基本类型参数的情况下，可以直接在sql中取到

多个参数用Map，或者注解

# 7.配置解析
## 7.1 核心配置文件
- mybatis-config.xml
- MyBatis 的配置文件包含了会深深影响 MyBatis 行为的设置和属性信息。 配置文档的顶层结构如下


```xml
configuration（配置）
properties（属性）
settings（设置）
typeAliases（类型别名）
typeHandlers（类型处理器）
objectFactory（对象工厂）
plugins（插件）
environments（环境配置）
environment（环境变量）
transactionManager（事务管理器）
dataSource（数据源）
databaseIdProvider（数据库厂商标识）
mappers（映射器）
```
## 7.2 环境配置（environments）
MyBatis 可以配置成适应多种环境，这种机制有助于将 SQL 映射应用于多种数据库之中， 现实情况下有多种理由需要这么做。

**不过要记住：尽管可以配置多个环境，但每个 SqlSessionFactory 实例只能选择一种环境。在default中选择我们需要的环境，而对应的环境是id**

```xml
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE configuration
        PUBLIC "-//mybatis.org//DTD Config 3.0//EN"
        "http://mybatis.org/dtd/mybatis-3-config.dtd">
<!--核心配置文件-->
<configuration>
<!--环境-->
    <environments default="test">
        <environment id="development">
            <transactionManager type="JDBC"/>
            <dataSource type="POOLED">
                <!-- 驱动-->
                <property name="driver" value="com.mysql.cj.jdbc.Driver"/>
                <property name="url" value="jdbc:mysql://localhost:3306/mybatis?useSSL=false&amp;serverTimezone=UTC"/>
                <property name="username" value="root"/>
                <property name="password" value="123456"/>
            </dataSource>
        </environment>
        <environment id="test">
            <transactionManager type="JDBC"/>
            <dataSource type="POOLED">
                <!-- 驱动-->
                <property name="driver" value="com.mysql.cj.jdbc.Driver"/>
                <property name="url" value="jdbc:mysql://localhost:3306/mybatis?useSSL=false&amp;serverTimezone=UTC"/>
                <property name="username" value="root"/>
                <property name="password" value="123456"/>
            </dataSource>
        </environment>
    </environments>
    <mappers>
        <mapper resource="com/kuang/dao/UserMapper.xml"/>
    </mappers>
</configuration>
```

Mybatis默认的事务管理器就是JDBC，连接池:POOLED。
## 7.3 属性（properties）
我们可以通过properties属性来实现引用配置文件。

这些属性都是可外部配置且可动态替换的，既可以在典型的Java属性文件中配置，亦可通过properties元素的子元素来传递。
>这里的java属性文件是指db.properties

```xml
<environment id="development">
    <transactionManager type="JDBC"/>
    <dataSource type="POOLED">
        <!-- 驱动-->
        <property name="driver" value="com.mysql.cj.jdbc.Driver"/>
        <property name="url" value="jdbc:mysql://localhost:3306/mybatis?useSSL=false&amp;serverTimezone=UTC"/>
        <property name="username" value="root"/>
        <property name="password" value="123456"/>
    </dataSource>
</environment>
```

```c
jdbc.jdbcUrl=jdbc:mysql://localhost:3306/ssm_crud
jdbc.driverClass=com.mysql.jdbc.Driver
jdbc.user=root
jdbc.password=123456
```

```xml
<properties resource="db.properties">
<dataSource type="POOLED">
<property name="jdbcUrl" value="${jdbc.jdbcUrl}"></property>
<property name="driverClass" value="${jdbc.driverClass}"></property>
<property name="user" value="${jdbc.user}"></property>
<property name="password" value="${jdbc.password}"></property>
</dataSource>
```
可以直接引入外部文件
可以在其中增加一些属性配置
**如果两个文件有同一个字段，优先使用外部配置文件的**
## 7.4 类型别名（typeAliases）
类型别名可为 Java 类型设置一个缩写名字。 它仅用于 XML 配置，意在降低冗余的全限定类名书写。例如：

```xml
<typeAliases>
  <typeAlias alias="Author" type="domain.blog.Author"/>
  <typeAlias alias="Blog" type="domain.blog.Blog"/>
  <typeAlias alias="Comment" type="domain.blog.Comment"/>
  <typeAlias alias="Post" type="domain.blog.Post"/>
  <typeAlias alias="Section" type="domain.blog.Section"/>
  <typeAlias alias="Tag" type="domain.blog.Tag"/>
</typeAliases>
```

当这样配置时，Blog 可以用在任何使用domain.blog.Blog 的地方。
也可以指定一个包名，MyBatis 会在包名下面搜索需要的 Java Bean，比如：

```xml
<typeAliases>
  <package name="domain.blog"/>
</typeAliases>
```

每一个在包 domain.blog 中的 Java Bean，在没有注解的情况下，会使用 Bean 的首字母小写的非限定类名来作为它的别名。 比如 domain.blog.Author 的别名为 author；若有注解，则别名为其注解值。见下面的例子：

```java
@Alias("author")
public class Author {
    ...
}
```
## 7.5 设置（settings）
这是 MyBatis 中极为重要的调整设置，它们会改变 MyBatis 的运行时行为。 下表描述了设置中各项设置的含义、默认值等。

![在这里插入图片描述](https://img-blog.csdnimg.cn/cd1979ec9056422e99f144e0f4081545.png)
![在这里插入图片描述](https://img-blog.csdnimg.cn/14532e4b2c8e43f79afab872ffdf4dfe.png)
![在这里插入图片描述](https://img-blog.csdnimg.cn/d7787b276fe74925bf1a634e8c3277d2.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAc3BlY2lhbHdpbmU=,size_20,color_FFFFFF,t_70,g_se,x_16)
## 7.6 映射器（mappers）
我们需要告诉 MyBatis 到哪里去找到这些语句。
MapperRegistry:注册绑定我们的Mapper文件
**方法一：推荐使用**
```xml
<!-- 使用相对于类路径的资源引用,注意，我们的标签是resource的时候，我们是引进文件夹的形式**/**/**/*.xml -->
<mappers>
  <mapper resource="org/mybatis/builder/AuthorMapper.xml"/>
  <mapper resource="org/mybatis/builder/BlogMapper.xml"/>
  <mapper resource="org/mybatis/builder/PostMapper.xml"/>
</mappers>
```
**方式二：使用class文件绑定注册**
```xml
<!-- 使用映射器接口实现类的完全限定类名 注意，我们的标签是class的时候，我们是引进文件夹的形式是
**.**.**.*.class-->
<mappers>
  <mapper class="org.mybatis.builder.AuthorMapper"/>
  <mapper class="org.mybatis.builder.BlogMapper"/>
  <mapper class="org.mybatis.builder.PostMapper"/>
</mappers>
```
**特别注意：**
- 接口和他的Mapper配置文件必须同名
- 接口和他的Mapper配置文件必须在同一个包下

**方式三：使用扫描包进行绑定**
```xml
<!-- 将包内的映射器接口实现全部注册为映射器 -->
<mappers>
  <package name="org.mybatis.builder"/>
</mappers>
```
接口和他的Mapper配置文件必须同名
接口和他的Mapper配置文件必须在同一个包下
## 7.7 作用域（Scope）和生命周期
生命周期类别是至关重要的，因为错误的使用会导致非常严重的**并发问题。**

![在这里插入图片描述](https://img-blog.csdnimg.cn/80e5246f2ec540e19a0f0855b49db823.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAc3BlY2lhbHdpbmU=,size_20,color_FFFFFF,t_70,g_se,x_16)
## 7.8 SqlSessionFactoryBuilder
- 这个类可以被实例化、使用和丢弃，一旦创建了 SqlSessionFactory，就不再需要它了。
- **局部变量**
## 7.9 SqlSessionFactory
- SqlSessionFactory 一旦被创建就应该在应用的运行期间一直存在，**没有任何理由丢弃它或重新创建另一个实例**。 
- **数据库连接池**
- 最简单的就是使用单例模式或者静态单例模式，**全局变量**
## 7.10 SqlSession
- 每个线程都应该有它自己的 SqlSession 实例。
- 连接到池的**请求**，需要关闭
- SqlSession 的实例不是线程安全的，因此是不能被共享的，所以它的最佳的作用域是请求或方法作用域
- 用完需要关闭，否则资源被占用
![在这里插入图片描述](https://img-blog.csdnimg.cn/c3a022c7392b43168f8bb1613f772d58.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAc3BlY2lhbHdpbmU=,size_20,color_FFFFFF,t_70,g_se,x_16)
这里的每一个mapper都是为了代表一个具体的事务。


## 7.11 resultMap
结果集映射
```c
id name pwd
id name password
```

```xml
    <resultMap id="UseMap" type="User">
<!--column是数据库的字段，property是实体类中的属性,只要对应的-->
        <result column="pwd" property="password"/>
    </resultMap>
```
```xml
   <select id="getUserById" resultMap="UseMap">
        select * from mybatis.user where id = #{id};
    </select>
```
resultMap 元素是 MyBatis 中最重要最强大的元素。

ResultMap 的设计思想是，对简单的语句做到零配置，对于复杂一点的语句，只需要描述语句之间的关系就行了。

# 9.解决属性名和字段名不一致的问题
1. 数据库字段
![在这里插入图片描述](https://img-blog.csdnimg.cn/e709872968f143c6a8413d2dc47078cc.png)
2. 我们在idea里面的user类

```java
public class User {
    private int id;
    private String name;
    private  String password;
}
```
这时候，我们返回的值password为null

如何解决：
- 1.起别名，小学生行为，没意思

```xml
<select id="getUserById" parameterType="int" resultType="com.kuang.pojo.User">
    select id,name ,pwd as pass word from f mybatis.user where id = #{id};
</select>
```
# 10.日志
## 10.1 日志工厂
如果一个数据库操作出现了异常，我们需要排错，日志是最好的助手。
曾经是:sout和debug
![在这里插入图片描述](https://img-blog.csdnimg.cn/0c86a5a9a6e9402e9f48c91e83be6e7f.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAc3BlY2lhbHdpbmU=,size_20,color_FFFFFF,t_70,g_se,x_16)
- SLF4J 
-  **LOG4J** 
- LOG4J2 
-  JDK_LOGGING 
- COMMONS_LOGGING
- **STDOUT_LOGGING** 
- NO_LOGGING

在Mybatis中具体使用那个一日志实现，在设置中设定!

## 10.2 STDOUT_LOGGING
在mybatis核心配置文件中
```xml
<settings>
    <setting name="logImpl" value="STDOUT_LOGGING"/>
</settings>
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/21a16b9f9c964ad3942e5086df67d951.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAc3BlY2lhbHdpbmU=,size_20,color_FFFFFF,t_70,g_se,x_16)
## 10.3 Log4j及对应的使用
- Log4j是Apache的一个开源项目，通过使用Log4j，我们可以控制日志信息输送的目的地是控制台、文件、GUI组件
- 我们也可以控制每一条日志的输出格式;
- 通过定义每一条日志信息的级别，我们能够更加细致地控制日志的生成过程。
- 通过一个配置文件来灵活地进行配置，而不需要修改应用的代码。

 **1.先导入log4j的包**

```xml
<dependency>
    <groupId>log4j</groupId>
    <artifactId>log4j</artifactId>
    <version>1.2.17</version>
</dependency>
```
**2.配置对应的properties**


```bash
log4j.appender.console = org.apache.log4j.ConsoleAppender
log4j.appender.console.Target = System.out
log4j.appender.console.Threshold=DEBUG
log4j.appender.console.layout = org.apache.log4j.PatternLayout
log4j.appender.console.layout.ConversionPattern=【%c】-%m%n

#文件输出的相关设置
log4j.appender.file = org.apache.log4j.RollingFileAppender
log4j.appender.file.File=./log/kuang.log
log4j.appender.file.MaxFileSize=10mb
log4j.appender.file.Threshold=DEBUG
log4j.appender.file.layout=org.apache.log4j.PatternLayout
log4j.appender.file.layout.ConversionPattern=【%p】【%d{yy-MM-dd}】【%c】%m%n

#日志输出级别
log4j.logger.org.mybatis=DEBUG
log4j.logger.java.sql=DEBUG
log4j.logger.java.sql.Statement=DEBUG
log4j.logger.java.sql.ResultSet=DEBUG
log4j.logger.java.sql.PreparedStatement=DEBUG
```
**3.配置对应的setting**

```xml
<settings>
    <setting name="logImpl" value="LOG4J"/>
</settings>
```
 **4.简单使用**

1. 在要使用Log4j的类中，导入包

```java
import org.apache.log4j.Logger;
```

2.日志对象，参数为当前类的class
```java
public class UserDaoTest {
    static  Logger logger = Logger.getLogger(UserDaoTest.class); }
```
3.日志级别

```java
logger.info("info:进入了testLog4j");
logger.debug("debug:进入了testLog4j");
logger.error("error:进入了testLog4j");
```
# 11.分页
为什么要分页？
- 减少数据的处理量

```
select * from user limit startIndex,pageSize
```
例子：
```cpp
select * from user limit 0,2;
```
下面的写法和上面的写法是相同的
```cpp
select * from user limit 2;
```
我们从第0个开始查每页显示两个，第一个是0号
## 11.1 使用使用Mybatis实现分页核心SQL
1.接口

```java
   List<User> getUserByLimit(Map<String,Integer> map);
```

2.Mapper.xml

```xml
<resultMap id="UserMap" type="com.kuang.pojo.User"/>
<!--    注意，我们这里的type的类型不能单单写User，如果要用typeliase要把它封装起来-->
    <select id="getUserByLimit" parameterType="map" resultMap="UserMap">
        select  * from mybatis.user limit #{startIndex},#{pagesize}
    </select>
```

3.测试
```java
@Test
public void getUserByLimit(){
    SqlSession sqlSession = MybatisUtils.getSqlSession();
    UserDao mapper = sqlSession.getMapper(UserDao.class);
    HashMap<String, Integer> map = new HashMap<String, Integer>();
    map.put("startIndex",0);
    map.put("pagesize",2);
    List<User> userByLimit = mapper.getUserByLimit(map);
    for (User user:userByLimit ){
        System.out.println(user);
    }
    sqlSession.close();
}
```

## 11.2 RowBounds分页
不再使用SQL实现分页
1.接口
```java
 List<User> getUserByRowBounds();
```
2.Mapper.xml

```xml
<select id="getUserByRowBounds" resultMap="UserMap">
    select * from mybatis.user
</select>
```
3.测试

```java
@Test
public void getUserByRowBounds(){
    SqlSession sqlSession = MybatisUtils.getSqlSession();
    //RowBounds实现
    RowBounds rowBounds = new RowBounds(1, 2);
    List<User> userList = sqlSession.selectList("com.kuang.dao.UserDao.getUserByRowBounds", rowBounds);
    for (User user:userList ){
        System.out.println(user);
    }
    sqlSession.close();
}
```
## 11.3 分页插件
这里的不推荐，但是我们可以查对应的文档即可使用，这里不具体介绍。

# 12.使用注解开发
## 12.1 面向接口编程
大家之前都学过面向对象编程，也学习过接口，但在真正的开发中，很多时候我们会选择面向接口编程

- **根本原因︰解耦，可拓展，提高复用，分层开发中，上层不用管具体的实现，大家都遵守共同的标准，使得开发变得容易，规范性更好**

在一个面向对象的系统中，系统的各种功能是由许许多多的不同对象协作完成的。在这种情况下，各个对象内部是如何实现自己的,对系统设计人员来讲就不那么重要了;

而各个对象之间的协作关系则成为系统设计的关键。小到不同类之间的通信，大到各模块之间的交互，在系统设计之初都是要着重考虑的，这也是系统设计的主要工作内容。面向接口编程就是指按照这种思想来编程。



## 12.2 关于接口的理解
接口从更深层次的理解，应是定义(规范，约束)与实现(名实分离的原则）的分离。
>假设一个项目由多个人去完成，比如只由一个人来完成接口问题，其他问题是不管的，实现交给其他人完成

接口的本身反映了系统设计人员对系统的抽象理解。
接口应有两类:
- 第一类是对一个个体的抽象，它可对应为一个抽象体(abstract class);
- 第二类是对一个个体某一方面的抽象，即形成一个抽象面(interface) ;-一个体有可能有多个抽象面。抽象体与抽象面是有区别的。

 **接口实例**
1. 接口

```java
 @Select("select * from user")
   List<User> getUsers();
```
2. 接口的绑定

```xml
<mappers>
    <mapper class="com.kuang.dao.UserMapper"/>
</mappers>
```

3. 测试
```java
@Test
public void test(){
    SqlSession sqlSession = MybatisUtils.getSqlSession();
    UserMapper mapper = sqlSession.getMapper(UserMapper.class);
    List<User> users = mapper.getUsers();
    for(User user:users){
        System.out.println(user);
    }
    sqlSession.close();
}
```

使用注解来映射简单语句会使代码显得更加简洁，但对于稍微复杂一点的语句，Java 注解不仅力不从心，还会让你本就复杂的 SQL 语句更加混乱不堪。 因此，**如果你需要做一些很复杂的操作，最好用 XML 来映射语句**。


本质上：是反射机制实现
底层里：动态代理

![在这里插入图片描述](https://img-blog.csdnimg.cn/120606427602490c8edb2a550b875b42.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAc3BlY2lhbHdpbmU=,size_20,color_FFFFFF,t_70,g_se,x_16)
## 12.3 CRUD
我们可以在工具类创建的时候实现自动提交事务!

```java
public class MybatisUtils {
    private static SqlSessionFactory sqlSessionFactory;
    static {
        try {
            //获取sqlSessionFactory
            String resource = "mybatis-config.xml";
            InputStream inputStream = Resources.getResourceAsStream(resource);
            sqlSessionFactory = new SqlSessionFactoryBuilder().build(inputStream);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    //既然有了 SqlSessionFactory，顾名思义，我们就可以从中获得 SqlSession 的实例了。
    // SqLSession完全包含了面向数据库执行SQL命令所需的所有方法。

    public static SqlSession getSqlSession(){
        return  sqlSessionFactory.openSession(true);
    }
}
```
编写接口

```java
   @Select("select * from user")
   List<User> getUsers();
```
测试类

```java
public void test(){
    SqlSession sqlSession = MybatisUtils.getSqlSession();
    UserMapper mapper = sqlSession.getMapper(UserMapper.class);
    List<User> users = mapper.getUsers();
    for(User user:users){
        System.out.println(user);
    }
    sqlSession.close();
}
```
**注意:我们必须要讲接口注册绑定到我们的核心配置文件中!**
## 12.4 关于@Param()注解
- 基本类型的参数或者String类型，需要加上
- 引用类型不需要加
- 如果只有一个基本类型的话，可以忽略，但是建议大家都加上!
- 我们在SQL中引用的就是我们这里的@Param("uid")中设定的属性名!


# 13.Mybatis详细执行流程
![在这里插入图片描述](https://img-blog.csdnimg.cn/8d443c33e4a84507907e40a136ca5169.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAc3BlY2lhbHdpbmU=,size_20,color_FFFFFF,t_70,g_se,x_16)

# 14.Lombok
Project Lombok is a java library that automatically plugs into your editor and build tools, spicing up your java.
Never write another getter or equals method again, with one annotation your class has a fully featured builder, Automate your logging variables, and much more.
## 14.1 使用步骤
1. 在setting导入插件，maven导入依赖

```xml
<!-- https://mvnrepository.com/artifact/org.projectlombok/lombok -->
<dependency>
    <groupId>org.projectlombok</groupId>
    <artifactId>lombok</artifactId>
    <version>1.18.12</version>
    <scope>provided</scope>
</dependency>
```
需要掌握
```cpp
@Getter and @Setter
@ToString
@EqualsAndHashCode
@AllArgsConstructor:有参构造,要和无参构造一起写
@NoArgsConstructor:无参构造
@Data:无参构造，get,set,toString,hashcode，equals
```
2.我们在具体类的时候简简单单

```java
import lombok.Data;
@Data
public class User {
    private int id;
    private String name;
    private  String pwd;

}
```
# 15.多对一处理
![在这里插入图片描述](https://img-blog.csdnimg.cn/cb4e3c85d65048249e2bdecfa3e63874.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAc3BlY2lhbHdpbmU=,size_14,color_FFFFFF,t_70,g_se,x_16)

```sql
CREATE TABLE `teacher` (
  `id` INT(10) NOT NULL,
  `name` VARCHAR(30) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=INNODB DEFAULT CHARSET=utf8

INSERT INTO teacher(`id`, `name`) VALUES (1, '秦老师'); 

CREATE TABLE `student` (
  `id` INT(10) NOT NULL,
  `name` VARCHAR(30) DEFAULT NULL,
  `tid` INT(10) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `fktid` (`tid`),
  CONSTRAINT `fktid` FOREIGN KEY (`tid`) REFERENCES `teacher` (`id`)
) ENGINE=INNODB DEFAULT CHARSET=utf8

INSERT INTO `student` (`id`, `name`, `tid`) VALUES (1, '小明', 1); 
INSERT INTO `student` (`id`, `name`, `tid`) VALUES (2, '小红', 1); 
INSERT INTO `student` (`id`, `name`, `tid`) VALUES (3, '小张', 1); 
INSERT INTO `student` (`id`, `name`, `tid`) VALUES (4, '小李', 1); 
INSERT INTO `student` (`id`, `name`, `tid`) VALUES (5, '小王', 1);
```

测试环境搭建
1. 导入lombok
2. 新建实体类Teacher,Student
3. 建立Mapper接口
4. 建立Mapper.XML
5. 在核心配置文件中绑定注册我们的Mapper接口或者文件!
**在配置的时候注意**

```xml
<mappers>
<!--当我们的xml文件和mybatis配置文件在同一个位置的时候我们不需要加上/-->
    <mapper class="com.kuang.dao.TeacherMapper"/>
    <mapper class="com.kuang.dao.StudentMapper"/>
</mappers>
```

7. 测试查询是否能够成功!

## 15.1 按照查询嵌套处理

```xml
<resultMap id="StudentTeacher" type="Student">
    <result property="id" column="id"/>
    <result property="name" column="name"/>
<!--复杂的属性我们需要单独处理
对象使用:association
集合使用:collection-->
    <association property="teacher" column="tid" javaType="Teacher" select="getTeacher"/>
</resultMap>
    <select id="getStudent" resultMap="StudentTeacher">
        select * from student;
    </select>
    <select id="getTeacher" resultType="Teacher">
        select  * from  teacher where id=#{id}
    </select>
```
## 15.2 按照结果嵌套处理

```xml
<resultMap id="StudentTeacher2" type="Student">
    <result property="id" column="sid"/>
    <result property="name" column="sname"/>
    <association property="teacher" javaType="Teacher">
        <result property="name" column="tname"/>
    </association>
</resultMap>



<select id="getStudent2" resultMap="StudentTeacher2">
    select s.id sid,s.name name,t.name tname
    from student s,teacher t
    where s.tid = t.id;
</select>
```
# 16.一对多处理
1. 环境搭建一样

```java
public class Teacher {
private  int id;
private  String name;
//一个老师拥有多个学生
    private List<Student> students;

}
```
```java
public class Student {
    private  int id;
    private  String name;
    private int tid;
}
```

2. 配置接口，xml 
<!--按结果嵌套查询-->
```java
public interface TeacherMapper {
    List<Teacher> getTeacher(@Param("tid") int id);
  	List<Teacher> getTeacher2(@Param("tid") int id);
}
```
## 16.1 按照查询嵌套处理（推荐）
```xml
<resultMap id="TeacherStudent" type="Teacher">
    <result property="id" column="sid"/>
    <result property="name" column="sname"/>
  <!--返回一个Teacher类的对象，其中有id,name,students三个属性,而students是Student类的集合，我们要将students映射到Student类的对应属性上-->
    <collection property="students" ofType="Student">
        <result property="id" column="sid"/>
        <result property="name" column="sname"/>
        <result property="tid" column="tid"/>
    </collection>
</resultMap>
    <select id="getTeacher" resultMap="TeacherStudent">
        select s.id sid,s.name sname,t.name tname,t.id tid
        from student s,teacher t
        where s.tid=t.id and t.id=#{tid}
    </select>
```
## 16.2 按照结果嵌套处理
```xml
<resultMap id="TeacherStudent2" type="Teacher">
    <collection property="students" javaType="Arraylist" ofType="Student" select="getStudentTeacherId" column="id"/>
</resultMap>

<select id="getTeacher2" resultMap="TeacherStudent2">
    select * from teacher where id = #{tid}
</select>
<select id="getStudentTeacherId" resultType="Student">
    select  * from student where tid =#{tid}
</select>
```
3. 测试

**小结**：
1. 关联- association（多对一）
2. 集合- collection （一对多）
3. javaType & ofType
	1. JavaType 用来指定实体类中属性的类型
	2. ofType用来指定映射到List或者集合中的pojo类型，泛型中的约束类型! |

**注意点**：
- 保证SQL的可读性，尽量保证通俗易懂
- 注意一对多和多对一中，属性名和字段的问题!
- 如果问题不好排查错误，可以使用日志，建议使用Log4j


>我们需要了解：
>1.Mysql引擎
>2.lnnoDB底层原理
>3.索引
>4.索引优化

# 16.动态SQL
**什么是动态SQL是根据不同的条件生成不同的SQL语句**
## 16.1 动态SQL环境搭建
1. 数据库的创建
```sql
CREATE TABLE `blog`(
`id` VARCHAR(50) NOT NULL COMMENT '博客id',
`title` VARCHAR(100) NOT NULL COMMENT '博客标题',
`author` VARCHAR(30) NOT NULL COMMENT '博客作者',
`create_time` DATETIME NOT NULL COMMENT '创建时间',
`views` INT(30) NOT NULL COMMENT '浏览量'
)ENGINE=INNODB DEFAULT CHARSET=utf8
```
2. 创建基础工程
1.导包
2.编写配置文件
3.编写实体类

```java
@Data
public class Blog {
    private int id;
    private  String title;
    private String author;
    private Date createTime;
    private int views;
}
```

4.编写实体类对应Mapper接口和Mapper.XML文件

## 16.2 动态SQL的常用标签
**1. IF语句**

```xml
<select id="queryBlogIF" parameterType="map" resultType="blog">
    select * from blog where 1=1
    <if test="title!=null">
      and title= #{title}  
    </if>
    <if test="author!=null">
        and author =#{author}
    </if>
</select>
```

**2. where标签**
where元素只会在至少有一个子元素的条件返回MYSQL子句的情况下才去插入WHERE子句。**而且，若语句的开头为AND或OR，where元素也会将它们去除。假如没有的话他还可以自动帮你加上。保证我们能正常查询输出。**
>推荐我们都写，可能不会自动加
```xml
<select id="queryBlogIF" parameterType="map" resultType="blog">
    select * from blog <where>
    <if test="title!=null">
      and title= #{title}  
    </if>
    <if test="author!=null">
      and author =#{author}
    </if>
</where>
```
**3. trim的set和choose标签**
1. choose标签(帮我自动除去and)
```xml
<!--假设都满足，还是只能走第一个！-->
    <select id="queryBlogChoose" resultType="Blog" parameterType="map">
        select  * from blog
        <where>
            <choose>
       <when test="title!=null">
           and title =#{title}
       </when>
<!--第一个可以不用加，但是第二个开始要加and-->
            and author = #{author}
        </when>
        <otherwise>
            and views=#{view}
        </otherwise>
            </choose>
        </where>
    </select>
```
2. set(可以帮我自动除去逗号）

```xml
<update id="updateBlog" parameterType="map" >
    update blog 
    <set>
        <if test="title!=null">
            title =#{title},
        </if>
        <if test="author!=null">
            author=#{author},
        </if>
    </set>
        where id =#{id}
</update>
```
>所谓的动态SQL本质还是SQL语句，只是我们可以在SQL层面增加一个逻辑代码

**4. SQL片段**
有的时候，我们可能会将一些功能的部分抽取出来，方便复用!
1. 使用Sql部分抽取公共的部分
```xml
<sql id="if-title-author">
    <if test="title!=null">
        title =#{title}
    </if>
    <if test="author!=null">
    author=#{author}
    </if>
</sql>
```
2. 用include插入即可
```xml
<select id="queryBlogIF" parameterType="map" resultType="blog">
    select * from blog
<where>
    <include refid="if-title-author"></include>
</where>
</select>
```
>注意事项：最好基于单表来定义我们的sql片段
>不要存在Where标签
>**5. foreach**

```xml
<select id="selectPostIn" resultType="domain.blog.Post">
  SELECT *
  FROM POST P
  WHERE ID in
  <foreach item="item" index="index" collection="list"
      open="(" separator="," close=")">
        #{item}
  </foreach>
</select>
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/d200b78cb2114e4ea4ac45f8fc0e2e68.png)

>list是一个集合，open是起始符，separator是分隔符，close是结尾符号，index是下标，每一次要取出的元素是item。

**关于使用该标签，我们建议使用map类型下的数组引入，即**
```java
HashMap map= new HashMap<>();
ArrayList<Integer> ids = new ArrayList<Integer>();
ids.add(1);
ids.add(2);
ids.add(3);
map.put("ids",ids);
```
## 16.3 动态SQL总结
**动态SQL就是在拼接SQL语句，我们只要保证SQL的正确性，按照SQL的格式，去排列组合就可以了!**
>建议在Mysql中写出sql，保证正确性再凭借动态sql
# 17.缓冲
![在这里插入图片描述](https://img-blog.csdnimg.cn/393d2b97046a4f24bffbe127073043c6.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAc3BlY2lhbHdpbmU=,size_19,color_FFFFFF,t_70,g_se,x_16)
>我们查询相同数据的时候，我们只需要走缓冲，就可以不用连接数据库浪费资源
## 17.1 缓冲的定义
**1.什么是缓存**
 存在内存中的临时数据。将用户经常查询的数据放在缓存(内存)中，用户去查询数据就不用从磁盘上(关系型数据库数据文件)查询，从缓存中查询，从而提高查询效率，解决了高并发系统的性能问题。
**2.为什么使用缓存**
 减少和数据库的交互次数，减少系统开销，提高系统效率
 **3.什么样的数据能使用缓存?**
经常查询并且不经常改变的数据。
>一定是不经常改变的数据才用缓存
## 17.2 Mybatis缓存
MyBatis包含一个非常强大的查询缓存特性，它可以非常方便地定制和配置缓存。缓存可以极大的提升查询效率。

MyBatis系统中默认定义了两级缓存:**一级缓存和二级缓存**。

**1.默认情况下，只有一级缓存开启。(SqlSession级别的缓存，也称为本地缓存)。**
就好比我们每次写项目的的时候：

```java
SqlSession sqlSession = MybatisUtils.getSqlSession();
BlogMapper mapper = sqlSession.getMapper();
......
sqlSession.close();
```
当我们结束的时候会将它结束

**2.二级缓存需要手动开启和配置，他是基于namespace级别的缓存。**

**3.为了提高扩展性，MyBatis定义了缓存接口Cache。我们可以通过实现Cache接口来自定义二级缓存**

## 17.2.1一级缓存
**1. 一级缓存也叫本地会话缓存:sqlSession**
- 与数据库同一次会话期间查询到的数据会放在本地缓存中。
- 以后如果需要获取相同的数据，直接从缓存中拿，没必须再去查询数据库;
- 开启日志查看日志输出
![在这里插入图片描述](https://img-blog.csdnimg.cn/d52a1aff6e3540a4868cb6a82dfd72a9.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAc3BlY2lhbHdpbmU=,size_20,color_FFFFFF,t_70,g_se,x_16)

**2. 缓冲失效的情况**
1. 为了保持数据库的正确性，我们在**增删改**的时候系统会自动帮我们刷新缓冲，以防止**我们的数据获取不正确返回**。
2. 查询不同的Mapper.xml（对应sqlSession不一样）
3. 查询不同的东西
4. 自动清理缓存
```java
sqlSession.clearCache();
```
![在这里插入图片描述](https://img-blog.csdnimg.cn/c53ba41c5e674295bb4b142f4aed62ba.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAc3BlY2lhbHdpbmU=,size_20,color_FFFFFF,t_70,g_se,x_16)
**相当于一个Map**

## 17.2.2二级缓冲
- 二级缓存也叫全局缓存，一级缓存作用域太低了，所以诞生了二级缓存
- 基于namespace级别的缓存，一个名称空间，对应一个二级缓存。
- 工作机制
	- 一个会话查询一条数据，这个数据就会被放在当前会话的一级缓存中;
  	- 如果当前会话关闭了，这个会话对应的一级缓存就没了；**但是我们想要的是，会话关闭了，一级缓存中的数据被保存到二级缓存中;**
  	- 新的会话查询信息，就可以从二级缓存中获取内容;	
  	- 不同的mapper查出的数据会放在自己对应的缓存(map）中;


步骤:
1. 开启全局缓存
![在这里插入图片描述](https://img-blog.csdnimg.cn/8b76d4d942a94778982ac7caa654450e.png)
即在对应的核心配置文件中setting去写，**显示地开启的**
2. 在Mapper.xml使用也可以在单个对应的sql语句标签的个别定义
```xml
<cache/>
```
>我们可以在标签中显示看到对应的setting
>我们可以使用对应的官方参数，也可以使用自己设定的参数

```java
public  void  test(){
    SqlSession sqlSession = MybatisUtils.getSqlSession();
    SqlSession sqlSession2 = MybatisUtils.getSqlSession();

    UserMapper mapper = sqlSession.getMapper(UserMapper.class);
    User user = mapper.querUserById(1);
    System.out.println(user);
    sqlSession.close();

    UserMapper mapper2 = sqlSession2.getMapper(UserMapper.class);
    User user1 = mapper2.querUserById(1);
    System.out.println(user1);
    sqlSession.close();

}
```
在这种情况下还是只查一次
**经典错误：**
```
Caused by: java.io.NotSerializableException: com.kuang.pojo.User
```
我们要将我们的实体类进行序列化
```java
public class User implements Serializable {
    private int id;
    private String name;
    private String pwd;
}
```
我们要把我们的实体类进行实体化

**小结：**
- 只要开启了二级缓存，在同一个Mapper下就有效
- 所有的数据都会先放在一级缓存中;
- 只有当会话提交，或者关闭的时候，才会提交到二级

![在这里插入图片描述](https://img-blog.csdnimg.cn/d39c732816e24ec38d51b9f93d99b9bf.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAc3BlY2lhbHdpbmU=,size_20,color_FFFFFF,t_70,g_se,x_16)

**我们一般先查二级缓存的，再查一级缓存，最后查数据库内容**

# 18.自定义缓存-ehcache
Ehcache是一种广泛使用的开源ava分布式缓存。主要面向通用缓存

要在程序中使用Ehcache
1.添加依赖
2.在mapper.xml
```xml
<cache type="org.mybatis.caches.ehcache.EhcacheCache"/>
```
3.配置文件

```xml
<?xml version=1.0 encoding=UTF-8 ?>
<ehcache xmlns:xsi=http://www.w3.org/2001/XMLSchema-instance
         xsi:noNamespaceSchemaLocation=http://ehcache.org/ehcache.xsd
         updateCheck=false>

    <diskStore path=./tmpdir/Tmp_EhCache/>

    <defaultCache
            eternal=false
            maxElementsInMemory=10000
            overflowToDisk=false
            diskPersistent=false
            timeToIdleSeconds=1800
            timeToLiveSeconds=259200
            memoryStoreEvictionPolicy=LRU/>

    <cache
            name=cloud_user
            eternal=false
            maxElementsInMemory=5000
            overflowToDisk=false
            diskPersistent=false
            timeToIdleSeconds=1800
            timeToLiveSeconds=1800
            memoryStoreEvictionPolicy=LRU/>
</ehcache>
```

**但是特别注意我们一般用Redis数据缓存。**
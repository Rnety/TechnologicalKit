# 1.jQuery

## 1.1 为什么我们学jQuery

我们使用js的时候：

1. 不能添加多个入口函数（window.onload)，如果添加了多个，后面的会把前面的给覆盖。

2. 原生js的api名字都太长太难记。
3. 原生js有的时候代码元余。
4. 原生js中有些属性或者方法,有浏览器兼容问题。
5. 原生js容错率低。

因此我们为了进一步方便我们我们学jQuery

## 1.2 JQuery简介

jQuery就是一个封装了很多方法的javascript库。

我们学习jQuery，其实就是学习jQuery中封装的一大堆方法。

**jQuery的优势:**

1. 是可以写多个入口函数的。
2. jQuery的api名字都容易记忆。
3. jQuery代码简洁（隐式迭代)。
4. jQuery帮我们解决了浏览器兼容问题。
5. 容错率较高,前面的代码出来了间题,后面的代码不受影响。

## 1.3 JQuery版本问题

可以去官网给下载

[jQuery](https://jquery.com/)

目前的版本有

- 1.x ：支持老浏览器，停止更新
- 2.x ：不支持老浏览器，不更新
- 3.x ：不支持老浏览器，更新

![image-20210930182017256](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20210930182017256.png)

其中第一个和第二个分别是

- compressed压缩版也叫精简版，去掉了格式，体积小，用于发布

- uncompressed未压缩版也叫原版，有统一的格式，体积较大，方便阅读，用于测试、学习和开发

  

## 1.4.体验JQuery

### 1.4.1 引入JQuery

1. 我们在Webapp下建立statis/js文件夹

2. 放入我们的对应jquery-2.1.3.min.js包

3. 调试好本地配置，建立新的jsp文件

4. 设置路径问题

   ```jsp
   <%pageContext.setAttribute("APP_PATH",request.getContextPath());%>
   ```

5. 在头文件导入js文件

   ```jsp
   <head>
       <script type="text/javascript" src="${APP_PATH}/static/js/jquery-2.1.3.min.js"></script>
   </head>
   ```

### 1.4.2 写一个入口函数

入口函数写法如下：

第一种写法

```jsp
<script>
    $(document).ready(function(){
    ......
    });
</script>
```

第二中写法

```jsp
<script>
    $(function(){
    ......
    });
</script>
```

> 我们强烈推荐第二种写法

**jQuery入口函数和window .onload入口函数的区别：**

1. window.onload入口函数不能写多个,但是jQuery的入口函数是可以写多个的。

2. 执行时机不同。jQuery入口函数快于window .onload入口函数。jQuery入口函数要等待页面上dom树加载完后执行，
   window.onload要等待页面上所有的资源（dom树，外部css/js连接,图片）都加载完毕后执行。

### 1.4.3 操作元素

找到你要操作的元素（用jQuery选择器去找）,去操作他（给他添加属性,样式,文本...）

```jsp
<script>
    $(document).ready(function(){
    $("div").with(100).height(100).css('backgroundColor','red').text('hhh')
    });
</script>
```

这里我们把div设置宽高都是100px，背景为红色，文本内容为hhh

**其中我们的.是一种链式编程**

# 2.jQuery语法

## 2.1 $是一个函数

如果报了这个错误:$ is not defined,就说明没有引入jQuery文件。

我们进入源文件查看结构

```txt
(function(){

}());
```

说明它是一个自执行函数，其中有

```txt
window.jQuery = window.$ =jQuery;
```



结论：

1. 说明我们引入一个js文件，是会执行这js文件种的代码的。

2. jQuery文件是一个自执行函数,执行这个jQuery文件中的代码,其实就是执行这个自执行函数。

3. 这个自执行文件就是给window对象添加一个jQuery属性和$属性。

4. $和jQuery等价是一个函数

   ```jsp
   console.log(window.jQuery === window.$);
   ```

   输出true

推论：

1. 参数不同，效果也不一样，当我们的参数是一个匿名函数的时候它就成为了我们的入口函数

   ```jsp
   <script>
       $(function(){
       ......
       });
   </script>
   ```

2. 如果参数是一个字符串，则它是一个选择器，如果字符串是标签则，则会创建对应的标签

   ```jsp
   <script>
   	$('#one');
   </script>
   ```

   ```jsp
   <script>
       $('<div>这里是ceit实验室</div>');
   </script>
   ```

3. 如果参数是一个dom对象，它就会把这个dom对象转换成jQuery对象

   ```jsp
   <script>
       $(dom对象);
   </script>
   ```

## 2.2 dom对象

dom对象是原生js选择器获取到的对象

```txt
var x = document.getElementById("")
var y = document.getElementsByTagName("")
```

利用这种方法只能调用dom方法或者属性，不能调用jQuery的方法和属性

我们在控制台输出是

```jsp
<div id ='one'></div>
```



## 2.3 jQuery对象

jQuery对象是利用jQuery选择器获取到的对象

```txt
var x = $("#one")
```

只能调用jQuery的方法或者属性,不能调用原生jsdom对象的属性或者方法

我们在控制台输出是

![image-20210930192527523](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20210930192527523.png)



是一个伪数值，是dom对象的包装集，我们可以根据jQuery对象[下标]和jQuery对象.get(下标)直接把jQuery对象转换成dom对象

```jsp
<script>
    //假设x为jQuery对象，里面有两个dom对象
    var y = js[0]
    var y = js.get(0)
</script>
```



## 2.4 点击事件

1. 获取到按钮们

   ```
   var btns = document.getElementsByTagName( "button");
   ```

2. 给关灯按钮设置点击事件，dom对象

   ```
   btns[1].onclick = function () {
   $('body').css('backgroundColor','black');}
   ```

3. 给开灯按钮设置一个点击事件，jQuery对象

   ```txt
   $().click(function(){});
   ```

   例子：

   ```
   $(btns[0]).click(function(){alert('22');});
   ```

## 2.5 文本信息

1.获取信息

会获取到这个标签中所有的文本,包括后代元素的文本.

```txt
$().text();
```

假如包含了多个dom元素的jQuery对象，通过text()方法获取文本，会把所有dom元素的文本获取到

2.设置文本

给jQuery对象的标签设置文本

```txt
$().text();
```

参数就是要设置的文本，如果和掩盖的内容不同，会覆盖

> 假如里面有标签，不会把标签解析出来

假如包含了多个dom元素的jQuery对象，通过text()方法获取文本，会把所有dom元素的文本设置到，这是一种隐式迭代

# 3.选择器

## 3.1  jQuery基本选择器

| 名称       | 用法               | 描述                                   |
| :--------- | ------------------ | -------------------------------------- |
| ID选择器   | ${'#id'};          | 获取指定ID元素                         |
| 类选择器   | ${'.class'};       | 获取同一类class元素                    |
| 标签选择器 | ${'div'};          | 获取同一类标签的所有元素               |
| 并集选择器 | ${'div,p,li'};     | 获取逗号分隔元素，只要符合条件之一就可 |
| 交集选择器 | ${'div.redClass'}; | 获取class为元素redClass的div元素       |



## 3.2 jQuery层次选择器

| 名称       | 用法        | 描述                             |
| ---------- | ----------- | -------------------------------- |
| 子代选择器 | ${'ul>li'}; | 子类选择器，只获得儿子层级的元素 |
| 后代选择器 | ${'ul li'}; | 后代选择器，获得所有后代         |



## 3.3 jQuery过滤选择器

| 名称       | 用法          | 描述                                    |
| ---------- | ------------- | --------------------------------------- |
| :eq(index) | $('li:eq(2)') | 获取li元素下标为2的元素，下标从0开始    |
| :odd       | $('li:odd')   | 获取li元素下标为奇数的元素，下标从0开始 |
| :even      | $('li:even')  | 获取li元素下标为偶数的元素，下标从0开始 |



## 3.4  jQuery筛选选择器(方法)

| 名称       | 用法                       | 描述                                 |
| ---------- | -------------------------- | ------------------------------------ |
| index()    | ${'ul'}.index()            | 返回它在兄弟元素的排名，用var来接    |
| children() | ${'ul'}.children('li')     | 子类选择器                           |
| find()     | ${'ul'}.find('li')         | 后代选择器                           |
| siblings() | $('#first').siblings('li') | 兄弟结点不包括自己                   |
| parent()   | $('#first').parent();      | 父结点                               |
| eq(index)  | ${'li'}.eq(2)              | 获取li元素下标为2的元素，下标从0开始 |
| next()     | ${'li'}.next()             | 下一个兄弟                           |
| pre()      | ${'li'}.prev()             | 上一个兄弟                           |

# 4.方法

## 4.1 菜单

需求：

1. 给一级菜单li设置鼠标移入事件，二级菜单显示
2. 给一级菜单li设置鼠标离开事件，二级菜单隐藏

结构如下

```jsp
<div class="wrap">
    <ul>
        <li>
            <a href="">一级菜单</a>
            <ul>
                <li><a href="">二级菜单</a></li>
                <li><a href="">二级菜单</a></li>
                <li><a href="">二级菜单</a></li>
                <li><a href="">二级菜单</a></li>
            </ul>
        </li>
            <li>
            <a href="">一级菜单</a>
            <ul>
                <li><a href="">二级菜单</a></li>
                <li><a href="">二级菜单</a></li>
                <li><a href="">二级菜单</a></li>
                <li><a href="">二级菜单</a></li>
            </ul>
        </li>
    </ul>
</div>
```

1.获取一级菜单li

```jsp
$('.wrap>ul>li').mouseover(function(){

});
```

> 谁触发了这个事件，谁就是这个this，this还是一个dom对象

2.设置移入事件

```jsp
$('.wrap>ul>li').mouseover(function(){
	//$(this).children('ul').css('display','block');
$(this).children('ul').show();

});
```

> 孩子对象的只拿ul

3.设置移除事件

```jsp
$('.wrap>ul>li').mouseover(function(){
//$(this).children('ul').css('display','none');
	$(this).children('ul').hide();
});
```



**思考：为什么不给<a></a>设置鼠标移入和隐藏？**

a标签与二级菜单是兄弟，设置移入移出会导致我们无法访问二级菜单



**mouseover和mouseenter事件区别：**

我们的mouseover 事件在鼠标移动到选取元素及其子元素上触发

我们的mouseenter 事件在鼠标移动到选取元素上触发



**mouseleave和mouseout事件区别：**

我们的mouseout 事件在鼠标移动到选取元素及其子元素上触发

我们的mouseleave 事件在鼠标移动到选取元素上触发



**我们推荐使用mouseleave和mouseenter**

## 4.2 高亮显示

需求：

1.给小人物所在的li际签设置鼠标移入事件:当前li标签透明度为1,其他的兄弟li标签透明度为0.4

2.鼠标离开大盒子,所有的li标签的透明度改成1.

结构如下

```jsp
<div class="wrap">
    <ul>
        <li><a href=""><img src="1.jpg"/></a></li>
        <li><a href=""><img src="2.jpg"/></a></li>
        <li><a href=""><img src="3.jpg"/></a></li>
        <li><a href=""><img src="4.jpg"/></a></li>
        <li><a href=""><img src="5.jpg"/></a></li>
        <li><a href=""><img src="6.jpg"/></a></li>
        <li><a href=""><img src="7.jpg"/></a></li>
        <li><a href=""><img src="8.jpg"/></a></li>
    </ul>
</div>
```

1.移入

```jsp
$('.wrap').find('li').mouseenter(function(){

$(this).css('opacity',1).siblings('li').css('opacity',0.4)

});
```

>$(this).css('opacity',1)是有返回值，返回值还是它本身

2.移出

```jsp
$('.wrap').mouseleave(function(){

$(this).find('li').css('opacity',1)

});
```



jQuery特性:

1. 隐式迭代

2. 链式编程,在于一个方法返回的是一个jQuery对象，既然是jQueyr对象就可以继续点出jQuery的方法类



## 4.3 class类操作

### 4.3.1 添加类

1.添加一个类

```jsp
$('.wrap').addClass('类名');
```

2.添加多个类

```jsp
$('.wrap').addClass('类名1 类名2');
```

### 4.3.2 移出类

1.移出一个类

```jsp
$('.wrap').removeClass('类名');
```

2.移出多个类

```jsp
$('.wrap').removeClass('类名1 类名2');
```

3.移出所有类

```jsp
$('.wrap').removeClass();
```

### 4.3.3 判断类

判断是否我们的类中有这个类，返回值是boolean

```jsp
$('.wrap').hasClass('类名');
```

### 4.3.4 切换类

当我们元素中有这个类则移出，没有则添加

```jsp
$('.wrap').toggleClass('类名');
```

# 5.jQuery动画

jQuery提供了三组基本动画，这些动画都是标准的、有规律的效果，jQuery还提供了自定义动画的功能。

## 5.1 三组基本动画

- 显示(show)与隐藏(hide)是一组动画:

- 滑入(slideDown)与滑出(slideUp)与切换(slideToggle)，效果与卷帘门类似
- 淡入(fadeln)与淡出(fadeOut)与切换(fadeToggle)

**以优雅的动画显示所有匹配的元素，并在显示完成后可选地触发一个回调函数;指定时间后依次执行回调函数.**



**例子：**

页面上能找到几个，就连着执行几次。时间可以为毫秒数，也可以是slow,nomal,fast

```
1.$obj.show([speed], [callback]);
```

speed (可选):动画的执行时间

- 1.如果不传，就没有动画效果。如果是slide和fade系列，会默认为normal

- 2.毫秒值(比如1000),动画在1088毫秒执行完成(推荐)
- 3.固定字符串，slow(600)、normal(400)、fast(200)，如果传其他字符串，则默认为normal

 callback(可选):执行完动画后执行的回调函数

## 5.2 自定义

- animate

  ```jsp
  $(selector).animate({params},[easing],[callback]);
  //{params}:要执行动画的CSS属性，带数字（必选)
  //speed :执行动画时长(可选)
  //easing:执行效果，默认为swing(缓动)，可以是linear(匀速)
  //callback:动画执行完后立即执行的回调函数（可选)
  ```

## 5.3 动画队列与停止动画

- 在同一个元素上执行多个动画，那么对于这个动画来说，后面的动画会被放到动画队列中，等前面的动画执行完成了才会执行(联想:火车进站)。

  ```jsp
  //stop方法：停止动画效果
  stop(clearQueue,jumpToEnd);
  //两个参数都是boolean类型的
  //第一个参数：是否清除队列
  //第二个参数：是否跳转到最终效果
  ```

# 6.jQuery节点操作

## 6.1 创建节点

原生js中创建节点:

- document.write(); 
- innerHTML; 
- document.createElement();

### 6.1.1 html();

- 1.1 获取内容

```jsp
//获取id为div1的内容，获取所有元素内容
$('#div1').html();
```

- 1.2 设置内容

```jsp
//获取id为div1的内容，然后覆盖原来的内容
//当我们的字符串里面有标签的时候是可以被解析出来的
$('#div1').html('我是陆家贤');
```

### 6.1.2 $()

我们$(htm1Str)可以创建元素，但是创建的元素只能存在内存中

```jsp
//$(htm1Str)
//htmlStr:html格式的字符串
$('<span>这是一个span元素</span>');
```

如果要在页面上显示，就要追加.

```jsp
var link = $('<span>这是一个span元素</span>');
$('#div1').append(link);
```

### 6.1.3 案例

需求：

- 点击某个按钮tbody有对应的三个tr
- 每个tr里面有三个td
- 与上面的一一对应

```jsp
<input type="button" value="获取数据" id="j_btnGetData">
<table>
    <thead>
        <tr>
            <th>标题</th>
            <th>地址</th>
            <th>说明</th>
        </tr>
    </thead>
    <tbody id='j_tbData'>
        
    </tbody>
</table>
```

我们有数据

![image-20211003011026585](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211003011026585.png)

1. 给获取数据按钮设置点击事件

   ```jsp
   $('#j_btnGetData').click(function(){
   
   });
   ```

#### 1. html()处理数据

一次性把内容添加进去

```text
$('#j_btnGetData').click(function(){
var list = [];
for(var i=0;i<data.length;i++){
      //tr                          
      list.push("<tr>");
      //td取决于我们的数据有多少个键值对，遍历对象
      for(var key in data[i]){
          list.push('<td>')                      		list.push(data[i][key])   
          list.push('</td>')                       }                          
      list.push("</tr>");                         	list.join("")//添加空字符串让整个都变成字符串
                                }
});
```

#### 2. $()

```text
$('#j_btnGetData').click(function(){

for(var i =0 ; i < data.length; i++){
var $tr = $("<tr><td>"+data[i]['name']+
"</td><td>"+data[i]['url']+"</td><td>"+
data[i]['type']+</td></tr>");


$('#j_tbData')lappend($tr);
}

});
```

## 6.2 添加节点

### 6.2.1 append()

**父元素.append(子元素)，而且是作为最后一个子元素添加**

1.新创建一个li标签,添加到ul1中的去.

```
var $liNew = $("<li>我是新创建的li标签</li>"); 
$('#ul1').append($liNew);
```

2.把ul1中已经存在的li标签添加到ul中去．剪切后作为最后一个子元素添加．

```
var $li3 = $('#li3');
$('#ul1').append($li3);
```

3.把ul2中已经存在的li标签添加到ul1中去.剪切后作为最后一个子元素添加．

```
var $li32= $('#li32');
$("#ul1').append($li32);
```

> 注意是剪切哦

### 6.2.2 prepend()

**父元素.append(子元素)，而且是作为第一个一个子元素添加**

1.新创建一个li标签,添加到ul1中第一个前.

```
var $liNew = $("<li>我是新创建的li标签</li>"); 
$('#ul1').prepend($liNew);
```

2.把ul1中已经存在的li标签添加到ul中去．剪切后作为第一个子元素添加．

```
var $li3 = $('#li3');
$('#ul1').prepend($li3);
```

3.把ul2中已经存在的li标签添加到ul1中去.剪切后作为第一个子元素添加．

```
var $li32= $('#li32');
$("#ul1').prepend($li32);
```

> 注意是剪切哦

### 6.2.3 before()

**元素A. before(B)，把元素B插入A的后面，作为兄弟元素添加**

```
var $liNew = $("<li>我是新创建的li标签</li>"); 
$('#ul1').before($liNew);
```

### 6.2.3 after()

**元素A. before(B)，把元素B插入A的前面，作为兄弟元素添加**

```
var $liNew = $("<li>我是新创建的li标签</li>"); 
$('#ul1').after($liNew);
```

### 6.2.4 appendTo()

**子元素.append(父元素)，而且是子元素作为父元素最个一个子元素添加**

1.新创建一个li标签,添加到ul1中第一个前.

```
var $liNew = $("<li>我是新创建的li标签</li>"); 
$('$liNew').appendTo(#ul1);
```

### 6.2.5 案例

```jsp
<h1>
    城市选择
</h1>
<select id ="src-city" name="src-city" multiple>
     <option value="1">1</option>
     <option value="2">2</option>
     <option value="3">3</option>
     <option value="4">4</option>
     <option value="5">5</option>
     <option value="6">6</option>
</select>
<select id ="tar-city" name="src-city" multiple>

</select>
<button id="btn_sel_all"></button>
<button id="btn_sel_none"></button>
<button id="btn_sel"></button>
<button id="btn_back"></button>
```

1.全部到右边

```jsp
$(function(){
$('btn_sel_all').click(function(){
$('#src-city>option').appendTo($('#tar-city'))
});
});
```

2.全部到左边

```jsp
$(function(){
$('btn_sel_none').click(function(){
$('#tar-city>option').appendTo($('#src-city'))
});
});
```

3.选中到右边

```jsp
$(function(){
$('btn_sel').click(function(){
$('#src-city>option:selected').appendTo($('#tar-city'))
});
});
```

4.选中到左边

```jsp
$(function(){
$('btn_sel').click(function(){
$('#tar-city>option:selected').appendTo($('#src-city'))
});
});
```

## 6.3 移出节点和清除节点

1.清空节点的内容

```
$('').empty();
```

2.移出某个元素

```
$('').remove();
```

## 6.4 克隆节点

克隆的节点只存在内存中，需要用append添加

```jsp
var cloneDiv = $('#div1').clone();
$('body').append(cloneDiv);
```

克隆事件是有参数的，分别是true和false，当我们是true时候我们会把事件一起克隆过去，在jQuery中我们的参数默认是false



修改节点id

```jsp
var cloneDiv = $('#div1').clone();
cloneDiv.attr('id','div2')
$('body').append(cloneDiv);
```

# 7.jQuery操作属性

## 7.1 val()

1.获取表单的内容

```jsp
$('#txt').val();
```

2.设置表单参数的值

```jsp
$('#txt').val('我是设置的值');
```

案例需求：

- 点击添加数据按钮,显示添加面板和遮罩层.
- 点击添加面板里的关闭按钮,隐藏添加面板和遮罩层.
- 点击添加面板里的添加按钮,会把输入的内容生成一个tr,这个tr添加到tbody中
- 点击delete这些a标签,删除对应的tr.

1.点击添加数据按钮,显示添加面板和遮罩层.

```jsp
$('添加数据按钮id').click(function(){
	$('模态框id').show();
	$('遮罩层id').show();
});
```

2.点击添加面板里的关闭按钮,隐藏添加面板和遮罩层.

```jsp
$('关闭按钮id').click(function(){
	$('模态框id').hide();
	$('遮罩层id').hide();
});
```

3.点击添加面板里的添加按钮,会把输入的内容生成一个tr,这个tr添加到tbody中

```jsp
$('保存按钮id').click(function(){
	var texlession01 = $('输入的信息1').val();
	var texlession02 = $('输入的信息2').val();
	var trNew = $('标签'+texlession01+'反标签'+'标签'+texlession02+'反标签');
	$('tbody的id').append(trNew);
	$('关闭按钮id').click();
});
```

> 可以 trNew.find('').click(function(){ trNew.remove();});给它添加事件

4.点击delete这些a标签,删除对应的tr.

```jsp
$('tbody的id class类').click(function(){
	$(this).parent().parent().remove();
});
```

## 7.2 attr()

### 7.2.1 设置属性

attr两个参数有三种用法

- 第一种是以前就有的属性，修改这个属性
- 修改自定义属性
- 原来没有这个属性，添加这个属性并给它赋值

```jsp
$('id').attr('属性名','属性值')
```

### 7.2.2 获得属性

attr一个参数有三种用法

- 第一种是以前就有的属性，获得这个属性
- 获取自定义属性
- 原来没有这个属性，获取这个值就是undefined

```jsp
$('id').attr('属性名')
```

## 7.3 removeAttr()

### 7.3.1 移出单属性

```
$('id').removeAttr('属性名')
```

### 7.3.2 移出单属性

```
$('id').removeAttr('属性名1 属性名2 属性名3')
```

## 7.4 prop()

回忆一下，有一类属性比如: checked，写在元素的身上就表示选中，没有写在元素的身上就表示没有选中。

在jQuery1.6之后，对于checked selected、disabled这类boolean类型的属性来说，不能用attr方法，只能用prop方法。

```
//设置属性
$(': checked').prop('checked',true); 
//获取属性
$(': checked').prop('checked'); //返回true或者false
```

### 7.4.1 多选框

需求:

- 上面的多选框选中，下面的多选框们跟着选中，上面的多选框没有选中，下面的多选框们跟着不选中。
- 下面的多选框们，都有单击事件。
- 如果下面的多选框们都选中了，那么上面的那个多选框跟着选中，如果下面多选框有一个没有选中，那么上面的多选框就不选中。

1.上面的多选框选中，下面的多选框们跟着选中，上面的多选框没有选中，下面的多选框们跟着不选中。

```jsp
$('多选框id').click(function(){
var checkedValue = $(this).prop('checked')
$('下面所有的input').prop('checked',checkedValue)
});
```

2.下面的多选框们，都有单击事件。

```jsp
$('下面所有的input').click(function(){
//判断下面的那四个多选框是否都被选中了。
var numOfAll = $('下面所有的input').1ength;//获取到下面所有多选框的个数。
var numOfSelect = $('下面所有的input:checked').length;//获取到下面被选中的多选框的个数。
//判断
$('多选框id' ).prop('checked',numOfAll == numOfSelect);
});
```

# 8.jQuery尺寸和位置操作

## 8.1 width方法与height方法

设置或者获取高度，不包括内边距、边框和外边距

```
//带参数表示设置高度
$('img').height(200);

//不带参数获取高度
$('img').height();
```

获取网页的可视区宽高

```
//获取可视区宽度
$(window ).width();

//获取可视区高度
$(window ) .height();
```

## 8.2 width方法与height方法的inner和out扩展

```
innerwidth( )/innerHeight( )//方法返回元素的宽度/高度（包括内边距)。
outerwidth( )/outerHeight( )//方法返回元素的宽度/高度（包括内边距和边框)。
outerwidth(true)/outerHeight(tru)//方法返回元素的宽度/高度（包括内边距、边框和外边距)。
```

## 8.3 offset方法与position方法

offset方法获取元素距离document的位置，position方法获取的是元素距离有定位的父元素(offsetParent)的位置。

```jsp
//获取元素距离document的位置,返回值为对象:{left:100,top:100}
$(selector).offset();
//获取相对于其最近的有定位的父元素的位置。
$(selector).position();
```

## 8.4 scrollTop与scrollLeft

设置或者获取垂直滚动条的位置

```
//获取页面被卷曲的高度
$(window).scrollTop();
//获取页面被卷曲的宽度
$(window).scrollLeft();
//设置页面被卷曲的高度
$(window).scrollTop(数值);
//设置页面被卷曲的宽度
$(window).scrollLeft(数值);
```


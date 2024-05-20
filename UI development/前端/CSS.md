# CSS

## margin和padding的区别

- margin是指从自身边框到另一个容器边框之间的距离，就是容器外距离。（外边距）

- padding是指自身边框到自身内部另一个容器边框之间的距离，就是容器内距离。（内边距）

![image-20211102222245792](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211102222245792.png)

## before 选择器

### 定义和用法

:before 选择器在被选元素的内容前面插入内容。

请使用 content 属性来指定要插入的内容。

```html
<style>
p:before
{
content:"台词：";
background-color:yellow;
color:red;
font-weight:bold;
}
</style>
```

```html
<!DOCTYPE html>
<html>
		<head></head>
    <body>
        <p>我是唐老鸭。</p>
        <p>我住在 Duckburg。</p>
    </body>
</html>
```

![image-20211102215525279](C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211102215525279.png)

### 以:before为例插入图片

对于一些小图标类型的图片，若使用<img>略微有些麻烦，iconfont是一个不错的选择用起来也相当灵活，但是所需要步骤较为繁琐，今天介绍一种使用css伪元素快速插入图标的小技巧。

<img src="C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211102215724122.png" alt="image-20211102215724122" style="zoom:50%;" />

### 伪类

> CSS 伪类 是添加到选择器的关键字，指定要选择的元素的特殊状态。

通俗来说就是： 我们要在某个元素处于某种状态时为其添加某个样式，但是仅仅通过dom树又无法表示这种状态，此时可以通过伪类对其添加样式。

比如当鼠标滑动过某个文字时将其变为红色，可使用伪类来实现：

```html
<body>
	<h1 class="title">伪类</h1>
	<style type="text/css">
		.title:hover{
			color: red;
		}
	</style>
</body>
```
### 伪元素

伪元素是一个附加至选择器末的关键词，允许你对被选择元素的特定部分修改样式[

通俗来说：我们可以使用伪元素创建在dom树中并不存在（在HTML文档中未定义这个元素，）的元素。话不多说上示例代码：

```html
<body>
    <!-- 在HTML文档中只定义了一个元素 -->
    <h1 class="title">HTML中定义的元素</h1>
    <style type="text/css">
        .title:hover{
            color: red;
        }
        /* 通过伪类增加一个元素 */
        .title::before{
            content: "伪类定义的元素";
            font-size: 12px;
            color: blue;
        }
    </style>
</body>
```

### 案例说明

弄清楚伪类与伪元素的区别之后，那我们就用伪元素来添加小图标。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200714191549165.png)

再看一眼效果图，我们要在 “5月14日” 前加上一个日历的小图标。

```html
<view class="date-text"><text>5月14日</text></view>
```



<text>5月14日</text>被包裹在 class=“date-text” 这一 <view></view> 元素内部，所以需要在view内部创建一个图片伪元素，具体操作看注释咯。

```js
.date-text {
	font-size: 28rpx;
	display: flex;
	margin: 0 20rpx;
	// scss 语法，相当于 .date-text::before
	&:before {
		content: '';
		display: block;
		// 定义元素位置
		margin-top: 12rpx;
		margin-right: 20rpx;
		// 定义元素宽高
		width: 36rpx;
		height: 36rpx;
		// background-image无法引用本地资源，故需要用网络地址
		background-image: url($url+'calendar.png');
		background-size: 100% 100%;
	}
	text {
		margin-top: 12rpx;
	}
}
```

## display属性

### 定义和用法

`display` 属性是用于控制布局的最重要的 CSS 属性。

`display `属性规定是否/如何显示元素。

每个 HTML 元素都有一个默认的 `display` 值，具体取决于它的元素类型。大多数元素的默认 `display` 值为 `block` 或` inline`。

`display` 属性规定元素应该生成的框的类型。

### 说明

这个属性用于定义建立布局时元素生成的显示框类型。对于 HTML 等文档类型，如果使用 display 不谨慎会很危险，因为可能违反 HTML 中已经定义的显示层次结构。对于 XML，由于 XML 没有内置的这种层次结构，所有 display 是绝对必要的。

**注释：**CSS2 中有值 compact 和 marker，不过由于缺乏广泛的支持，已经从 CSS2.1 中去除了。

| 默认值：          | inline                          |
| ----------------- | ------------------------------- |
| 继承性：          | no                              |
| 版本：            | CSS1                            |
| JavaScript 语法： | *object*.style.display="inline" |

### 可能的值

| 值                 | 描述                                                         |
| :----------------- | :----------------------------------------------------------- |
| none               | 此元素不会被显示。                                           |
| block              | 此元素将显示为块级元素，此元素前后会带有换行符。             |
| inline             | 默认。此元素会被显示为内联元素，元素前后没有换行符。         |
| inline-block       | 行内块元素。（CSS2.1 新增的值）                              |
| list-item          | 此元素会作为列表显示。                                       |
| run-in             | 此元素会根据上下文作为块级元素或内联元素显示。               |
| compact            | CSS 中有值 compact，不过由于缺乏广泛支持，已经从 CSS2.1 中删除。 |
| marker             | CSS 中有值 marker，不过由于缺乏广泛支持，已经从 CSS2.1 中删除。 |
| table              | 此元素会作为块级表格来显示（类似 <table>），表格前后带有换行符。 |
| inline-table       | 此元素会作为内联表格来显示（类似 <table>），表格前后没有换行符。 |
| table-row-group    | 此元素会作为一个或多个行的分组来显示（类似 <tbody>）。       |
| table-header-group | 此元素会作为一个或多个行的分组来显示（类似 <thead>）。       |
| table-footer-group | 此元素会作为一个或多个行的分组来显示（类似 <tfoot>）。       |
| table-row          | 此元素会作为一个表格行显示（类似 <tr>）。                    |
| table-column-group | 此元素会作为一个或多个列的分组来显示（类似 <colgroup>）。    |
| table-column       | 此元素会作为一个单元格列显示（类似 <col>）                   |
| table-cell         | 此元素会作为一个表格单元格显示（类似 <td> 和 <th>）          |
| table-caption      | 此元素会作为一个表格标题显示（类似 <caption>）               |
| inherit            | 规定应该从父元素继承 display 属性的值。                      |

### Display: none

`display: none `通常与 JavaScript 一起使用，以隐藏和显示元素，而无需删除和重新创建它们。

隐藏元素 `display:none` 还是 `visibility:hidden`？

- 通过将 display 属性设置为 none 可以隐藏元素。该元素将被隐藏，并且页面将显示为好像该元素不在其中：

```html
h1.hidden {
  display: none;
}
```

- 但是，该元素仍将占用与之前相同的空间。元素将被隐藏，但仍会影响布局：

```html
h1.hidden {
  visibility: hidden;
}
```

### 块级元素（block element）

块级元素总是从新行开始，并占据可用的全部宽度（尽可能向左和向右伸展）。

- `<div>`
- `<h1> - <h6>`
- `<p>`
- `<form>`
- `<header>`
- `<footer>`
- `<section>`

### 行内元素（inline element）

内联元素不从新行开始，仅占用所需的宽度。

这是段落中的行内 <span> 元素。

- `<span>`
- `<a>`
- `<img>`

### display: inline-block

- 与 display: inline 相比，主要区别在于 display: inline-block 允许在元素上设置宽度和高度。

同样，如果设置了 display: inline-block，将保留上下外边距/内边距，而 display: inline 则不会。

- 与 display: block 相比，主要区别在于 display：inline-block 在元素之后不添加换行符，因此该元素可以位于其他元素旁边。

下例展示 display: inline、display: inline-block 以及 display: block 的不同行为：

**使用 inline-block 来创建导航链接**

display 的一种常见用法：inline-block 用于水平而不是垂直地显示列表项。

我们在对应的li下面设置该样式

### 覆盖默认的 Display 值

如前所述，每个元素都有一个默认 display 值。但是，您可以覆盖它。

将行内元素更改为块元素，反之亦然，对于使页面以特定方式显示同时仍遵循 Web 标准很有用。

一个常见的例子是为实现水平菜单而生成行内的 <li> 元素

**注意：**设置元素的 display 属性仅会更改*元素的显示方式*，而不会更改元素的种类。因此，带有 **display: block;** 的行内元素不允许在其中包含其他块元素。

下例将 <span> 元素显示为块元素：

## width和max-width属性

### 使用width

块级元素始终占用可用的全部宽度（尽可能向左和向右伸展）。

设置块级元素的 width 将防止其延伸到其容器的边缘。

### 使用margin:auto

可以将外边距设置为 auto，以将元素在其容器中水平居中。元素将占用指定的宽度，剩余空间将在两个外边距之间平均分配

### 使用max-width

**注意：**当浏览器窗口小于元素的宽度时， **<div>** 会发生问题。浏览器会将水平滚动条添加到页面。

在这种情况下，使用 max-width 可以改善浏览器对小窗口的处理。为了使网站在小型设备上可用，这一点很重要

## CSS 定位

position 属性规定应用于元素的定位方法的类型。

有五个不同的位置值：

- static
- relative
- fixed
- absolute
- sticky

元素其实是使用 top、bottom、left 和 right 属性定位的。但是，除非首先设置了 position 属性，否则这些属性将不起作用。根据不同的 position 值，它们的工作方式也不同。

### static

HTML 元素默认情况下的定位方式为 static（静态）。

静态定位的元素不受 top、bottom、left 和 right 属性的影响。

position: static; 的元素不会以任何特殊方式定位；它始终根据页面的正常流进行定位：

### relative

relative 元素相对于其正常位置进行定位。

设置相对定位的元素的 top、right、bottom 和 left 属性将导致其偏离其正常位置进行调整。不会对其余内容进行调整来适应元素留下的任何空间。

### fixed

fixed 的元素是相对于视口定位的，这意味着即使滚动页面，它也始终位于同一位置。 top、right、bottom 和 left 属性用于定位此元素。

固定定位的元素不会在页面中通常应放置的位置上留出空隙。

### absolute

absolute 的元素相对于最近的定位祖先元素进行定位（而不是相对于视口定位，如 fixed）。

然而，如果绝对定位的元素没有祖先，它将使用文档主体（body），并随页面滚动一起移动。

**注意：**“被定位的”元素是其位置除 **static** 以外的任何元素。

### sticky(重点)

sticky 的元素根据用户的滚动位置进行定位。

粘性元素根据滚动位置在相对（relative）和固定（fixed）之间切换。起先它会被相对定位，直到在视口中遇到给定的偏移位置为止 - 然后将其“粘贴”在适当的位置（比如 position:fixed）。

```html
<!DOCTYPE html>
<html>
<head>
<style>
div.sticky {
  position: -webkit-sticky;
  position: sticky;
  top: 0;
  padding: 5px;
  background-color: #cae8ca;
  border: 2px solid #4CAF50;
}
</style>
</head>
<body>

<p>请试着在这个框架内<b>滚动</b>页面，以理解粘性定位的原理。</p>

<div class="sticky">我是有粘性的！</div>

<div style="padding-bottom:2000px">
  <p>在此例中，当您到达元素的滚动位置时，粘性元素将停留在页面顶部（top: 0）。</p>
  <p>向上滚动以消除粘性。</p>
  <p>一些启用滚动的文本.. Lorem ipsum dolor sit amet, illum definitiones no quo, maluisset concludaturque et eum, altera fabulas ut quo. Atqui causae gloriatur ius te, id agam omnis evertitur eum. Affert laboramus repudiandae nec et. Inciderint efficiantur his ad. Eum no molestiae voluptatibus.</p>
  <p>一些启用滚动的文本.. Lorem ipsum dolor sit amet, illum definitiones no quo, maluisset concludaturque et eum, altera fabulas ut quo. Atqui causae gloriatur ius te, id agam omnis evertitur eum. Affert laboramus repudiandae nec et. Inciderint efficiantur his ad. Eum no molestiae voluptatibus.</p>
</div>

</body>
</html>

```

在此例中，在到达其滚动位置时，sticky 元素将停留在页面顶部（top: 0）。

### z-index

在对元素进行定位时，它们可以与其他元素重叠。

z-index 属性指定元素的堆栈顺序（哪个元素应放置在其他元素的前面或后面）。

元素可以设置正或负的堆叠顺序：

具有较高堆叠顺序的元素始终位于具有较低堆叠顺序的元素之前。

**注意：**如果两个定位的元素重叠而未指定 **z-index**，则位于 HTML 代码中最后的元素将显示在顶部。

## CSS 溢出

### Overflow

**overflow 属性控制对太大而区域无法容纳的内容的处理方式**

`overflow` 属性指定在元素的内容太大而无法放入指定区域时是剪裁内容还是添加滚动条。

`overflow` 属性可设置以下值：

- `visible` - **默认**。溢出没有被剪裁。内容在元素框外渲染
- `hidden` - 溢出被剪裁，其余内容将不可见
- `scroll` - 溢出被剪裁，同时添加滚动条以查看其余内容
- `auto` - 与 `scroll` 类似，但仅在必要时添加滚动条

**注释：**`overflow` 属性仅适用于具有指定高度的块元素。

### overflow-x 和 overflow-y

overflow-x 和 overflow-y 属性规定是仅水平还是垂直地（或同时）更改内容的溢出：

- overflow-x 指定如何处理内容的左/右边缘。
- overflow-y 指定如何处理内容的上/下边缘。

当您希望更好地控制布局时，可以使用 overflow

## CSS 浮动

### float 属性

float 属性用于定位和格式化内容，例如让图像向左浮动到容器中的文本那里。

float 属性可以设置以下值之一：

- left - 元素浮动到其容器的左侧
- right - 元素浮动在其容器的右侧
- none - 元素不会浮动（将显示在文本中刚出现的位置）。默认值。
- inherit - 元素继承其父级的 float 值

**最简单的用法是，float 属性可实现（报纸上）文字包围图片的效果。**

## CSS 浮动清除

### clear 属性

clear 属性指定哪些元素可以浮动于被清除元素的旁边以及哪一侧。

clear 属性可设置以下值之一：

- none - 允许两侧都有浮动元素。默认值
- left - 左侧不允许浮动元素
- right- 右侧不允许浮动元素
- both - 左侧或右侧均不允许浮动元素
- inherit - 元素继承其父级的 clear 值

使用 clear 属性的最常见用法是在元素上使用了 float 属性之后。

在清除浮动时，应该对清除与浮动进行匹配：如果某个元素浮动到左侧，则应清除左侧。您的浮动元素会继续浮动，但是被清除的元素将显示在其下方。

下例将清除向左的浮动。表示在（div 的）左侧不允许出现浮动元素

### Clearfix

只要您能够控制外边距和内边距（否则您可能会看到滚动条），overflow: auto clearfix 就会很好地工作。但是，新的现代 clearfix hack 技术使用起来更安全，以下代码被应用于多数网站：

```js
.clearfix::after {
  content: "";
  clear: both;
  display: table;
}
```

## CSS 浮动实例

```html
<!DOCTYPE html>
<html>
<head>
<style>
* {
  box-sizing: border-box;
}

.box {
  float: left;
  width: 33.33%;
  padding: 25px 25px;
}

.clearfix::after {   /*如果这里没有这个则下面的div会占上来*/
  content: "";
  clear: both;
  display: table;
}
</style>
</head>
<body>

<h1>网格框</h1>

<p>并排浮动的框：</p>

<div class="clearfix">
  <div class="box" style="background-color:#bbb">
  <p>框中的一些文本。</p>
  </div>
  <div class="box" style="background-color:#ccc">
  <p>框中的一些文本。</p>
  </div>
  <div class="box" style="background-color:#ddd">
  <p>框中的一些文本。</p>
  </div>
</div>

<p>请注意，我们还用了 clearfix hack 来处理布局流，并添加了 box-sizing 属性，以确保框不会由于额外的内边距（填充）而损坏。尝试删除此代码以查看效果。</p>

</body>
</html>

```

<img src="C:\Users\333\AppData\Roaming\Typora\typora-user-images\image-20211103142051840.png" alt="image-20211103142051840"  />

建议：

- 用padding来处理不同框下的距离
- 用固定的height来让他达到同一高度

```html
<!DOCTYPE html>
<html>
<head>
<style>
ul {
  list-style-type: none;	/*消去ul下面li的实心圆*/
  margin: 0;				/*可以根据F12慢慢调*/
  padding: 0;
  overflow: hidden;         /*把我们的ul隐藏*/
  background-color: #333;
}

li {
  float: left;				/*用浮动把他们排序好*/
}
	
li a {                         
  display: inline-block;   /*<a>标签是行内原始，我们化成对应的行内块*/
  color: white;
  text-align: center;
  padding: 14px 16px;		
  text-decoration: none;
}

li a:hover {                   /*设置鼠标移动时候显示的按钮背景*/
  background-color: #111;
}

.active {						/*设置当前的在页面*/
  background-color: red;
}
</style>
</head>
<body>

<ul>
  <li><a href="#home" class="active">Home</a></li>
  <li><a href="#news">News</a></li>
  <li><a href="#contact">Contact</a></li>
  <li><a href="#about">About</a></li>
</ul>

</body>
</html>
```

## CSS 水平和垂直对齐

### 居中对齐元素

要使块元素（例如 <div> ）水平居中，请使用 margin: auto;。

设置元素的宽度将防止其延伸到容器的边缘。

然后，元素将占用指定的宽度，剩余空间将在两个外边距之间平均分配：

**注意：**如果未设置 **width** 属性（或将其设置为 100％），则居中对齐无效。

### 居中对齐文本

如果仅需在元素内居中文本，请使用 text-align: center

## CSS 组合器

组合器是解释选择器之间关系的某种机制。

CSS 选择器可以包含多个简单选择器。在简单选择器之间，我们可以包含一个组合器。

CSS 中有四种不同的组合器：

- 后代选择器 (空格)
- 子选择器 (>)
- 相邻兄弟选择器 (+)
- 通用兄弟选择器 (~)

### 所有 CSS 组合选择器

| 选择器                                                       | 示例    | 示例描述                                   |
| :----------------------------------------------------------- | :------ | :----------------------------------------- |
| [*element* *element*](https://www.w3school.com.cn/cssref/selector_element_element.asp) | div p   | 选择 <div> 元素内的所有 <p> 元素。         |
| [*element*>*element*](https://www.w3school.com.cn/cssref/selector_element_gt.asp) | div > p | 选择其父元素是 <div> 元素的所有 <p> 元素。 |
| [*element*+*element*](https://www.w3school.com.cn/cssref/selector_element_plus.asp) | div + p | 选择所有紧随 <div> 元素之后的 <p> 元素。   |
| [*element1*~*element2*](https://www.w3school.com.cn/cssref/selector_gen_sibling.asp) | p ~ ul  | 选择前面有 <p> 元素的每个 <ul> 元素。      |

## CSS伪类

### 伪类

> CSS 伪类 是添加到选择器的关键字，指定要选择的元素的特殊状态。

通俗来说就是： 我们要在某个元素处于某种状态时为其添加某个样式，但是仅仅通过dom树又无法表示这种状态，此时可以通过伪类对其添加样式。

例如，它可以用于：

- 设置鼠标悬停在元素上时的样式
- 为已访问和未访问链接设置不同的样式
- 设置元素获得焦点时的样式

比如当鼠标滑动过某个文字时将其变为红色，可使用伪类来实现：

```html
<body>
	<h1 class="title">伪类</h1>
	<style type="text/css">
		.title:hover{
			color: red;
		}
	</style>
</body>
```

**注意：**`a:hover` 必须在 CSS 定义中的 `a:link` 和 `a:visited` 之后，才能生效！`a:active` 必须在 CSS 定义中的 `a:hover` 之后才能生效！伪类名称对大小写不敏感。

总结了一个便于记忆的“爱恨原则”（LoVe/HAte），即四种伪类的首字母:LVHA。

再重复一遍正确的顺序：a:link、a:visited、a:hover、a:active .

- 鼠标经过的“未访问链接”同时拥有a:link、a:hover两种属性，后面的属性会覆盖前面的属性定义；
- 鼠标经过的“已访问链接”同时拥有a:visited、a:hover两种属性，后面的属性会覆盖前面的属性定义；

### 所有 CSS 伪类

| 选择器                                                       | 例子                  | 例子描述                                                     |
| :----------------------------------------------------------- | :-------------------- | :----------------------------------------------------------- |
| [:active](https://www.w3school.com.cn/cssref/selector_active.asp) | a:active              | 选择活动的链接。                                             |
| [:checked](https://www.w3school.com.cn/cssref/selector_checked.asp) | input:checked         | 选择每个被选中的 <input> 元素。                              |
| [:disabled](https://www.w3school.com.cn/cssref/selector_disabled.asp) | input:disabled        | 选择每个被禁用的 <input> 元素。                              |
| [:empty](https://www.w3school.com.cn/cssref/selector_empty.asp) | p:empty               | 选择没有子元素的每个 <p> 元素。                              |
| [:enabled](https://www.w3school.com.cn/cssref/selector_enabled.asp) | input:enabled         | 选择每个已启用的 <input> 元素。                              |
| [:first-child](https://www.w3school.com.cn/cssref/selector_first-child.asp) | p:first-child         | 选择作为其父的首个子元素的每个 <p> 元素。                    |
| [:first-of-type](https://www.w3school.com.cn/cssref/selector_first-of-type.asp) | p:first-of-type       | 选择作为其父的首个 <p> 元素的每个 <p> 元素。                 |
| [:focus](https://www.w3school.com.cn/cssref/selector_focus.asp) | input:focus           | 选择获得焦点的 <input> 元素。                                |
| [:hover](https://www.w3school.com.cn/cssref/selector_hover.asp) | a:hover               | 选择鼠标悬停其上的链接。                                     |
| [:in-range](https://www.w3school.com.cn/cssref/selector_in-range.asp) | input:in-range        | 选择具有指定范围内的值的 <input> 元素。                      |
| [:invalid](https://www.w3school.com.cn/cssref/selector_invalid.asp) | input:invalid         | 选择所有具有无效值的 <input> 元素。                          |
| [:lang(*language*)](https://www.w3school.com.cn/cssref/selector_lang.asp) | p:lang(it)            | 选择每个 lang 属性值以 "it" 开头的 <p> 元素。                |
| [:last-child](https://www.w3school.com.cn/cssref/selector_last-child.asp) | p:last-child          | 选择作为其父的最后一个子元素的每个 <p> 元素。                |
| [:last-of-type](https://www.w3school.com.cn/cssref/selector_last-of-type.asp) | p:last-of-type        | 选择作为其父的最后一个 <p> 元素的每个 <p> 元素。             |
| [:link](https://www.w3school.com.cn/cssref/selector_link.asp) | a:link                | 选择所有未被访问的链接。                                     |
| [:not(*selector*)](https://www.w3school.com.cn/cssref/selector_not.asp) | :not(p)               | 选择每个非 <p> 元素的元素。                                  |
| [:nth-child(*n*)](https://www.w3school.com.cn/cssref/selector_nth-child.asp) | p:nth-child(2)        | 选择作为其父的第二个子元素的每个 <p> 元素。                  |
| [:nth-last-child(*n*)](https://www.w3school.com.cn/cssref/selector_nth-last-child.asp) | p:nth-last-child(2)   | 选择作为父的第二个子元素的每个<p>元素，从最后一个子元素计数。 |
| [:nth-last-of-type(*n*)](https://www.w3school.com.cn/cssref/selector_nth-last-of-type.asp) | p:nth-last-of-type(2) | 选择作为父的第二个<p>元素的每个<p>元素，从最后一个子元素计数 |
| [:nth-of-type(*n*)](https://www.w3school.com.cn/cssref/selector_nth-of-type.asp) | p:nth-of-type(2)      | 选择作为其父的第二个 <p> 元素的每个 <p> 元素。               |
| [:only-of-type](https://www.w3school.com.cn/cssref/selector_only-of-type.asp) | p:only-of-type        | 选择作为其父的唯一 <p> 元素的每个 <p> 元素。                 |
| [:only-child](https://www.w3school.com.cn/cssref/selector_only-child.asp) | p:only-child          | 选择作为其父的唯一子元素的 <p> 元素。                        |
| [:optional](https://www.w3school.com.cn/cssref/selector_optional.asp) | input:optional        | 选择不带 "required" 属性的 <input> 元素。                    |
| [:out-of-range](https://www.w3school.com.cn/cssref/selector_out-of-range.asp) | input:out-of-range    | 选择值在指定范围之外的 <input> 元素。                        |
| [:read-only](https://www.w3school.com.cn/cssref/selector_read-only.asp) | input:read-only       | 选择指定了 "readonly" 属性的 <input> 元素。                  |
| [:read-write](https://www.w3school.com.cn/cssref/selector_read-write.asp) | input:read-write      | 选择不带 "readonly" 属性的 <input> 元素。                    |
| [:required](https://www.w3school.com.cn/cssref/selector_required.asp) | input:required        | 选择指定了 "required" 属性的 <input> 元素。                  |
| [:root](https://www.w3school.com.cn/cssref/selector_root.asp) | root                  | 选择元素的根元素。                                           |
| [:target](https://www.w3school.com.cn/cssref/selector_target.asp) | #news:target          | 选择当前活动的 #news 元素（单击包含该锚名称的 URL）。        |
| [:valid](https://www.w3school.com.cn/cssref/selector_valid.asp) | input:valid           | 选择所有具有有效值的 <input> 元素。                          |
| [:visited](https://www.w3school.com.cn/cssref/selector_visited.asp) | a:visited             | 选择所有已访问的链接。                                       |

## CSS伪元素

伪元素是一个附加至选择器末的关键词，允许你对被选择元素的特定部分修改样式

CSS 伪元素用于设置元素指定部分的样式。

例如，它可用于：

- 设置元素的首字母、首行的样式
- 在元素的内容之前或之后插入内容

通俗来说：我们可以使用伪元素创建在dom树中并不存在（在HTML文档中未定义这个元素，）的元素。话不多说上示例代码：

```html
<body>
    <!-- 在HTML文档中只定义了一个元素 -->
    <h1 class="title">HTML中定义的元素</h1>
    <style type="text/css">
        .title:hover{
            color: red;
        }
        /* 通过伪类增加一个元素 */
        .title::before{
            content: "伪类定义的元素";
            font-size: 12px;
            color: blue;
        }
    </style>
</body>
```

### 案例说明

弄清楚伪类与伪元素的区别之后，那我们就用伪元素来添加小图标。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200714191549165.png)

再看一眼效果图，我们要在 “5月14日” 前加上一个日历的小图标。

```html
<view class="date-text"><text>5月14日</text></view>
```



<text>5月14日</text>被包裹在 class=“date-text” 这一 <view></view> 元素内部，所以需要在view内部创建一个图片伪元素，具体操作看注释咯。

```js
.date-text {
	font-size: 28rpx;
	display: flex;
	margin: 0 20rpx;
	// scss 语法，相当于 .date-text::before
	&:before {
		content: '';
		display: block;
		// 定义元素位置
		margin-top: 12rpx;
		margin-right: 20rpx;
		// 定义元素宽高
		width: 36rpx;
		height: 36rpx;
		// background-image无法引用本地资源，故需要用网络地址
		background-image: url($url+'calendar.png');
		background-size: 100% 100%;
	}
	text {
		margin-top: 12rpx;
	}
}
```

### 所有 CSS 伪元素

| 选择器                                                       | 例子            | 例子描述                      |
| :----------------------------------------------------------- | :-------------- | :---------------------------- |
| [::after](https://www.w3school.com.cn/cssref/selector_after.asp) | p::after        | 在每个 <p> 元素之后插入内容。 |
| [::before](https://www.w3school.com.cn/cssref/selector_before.asp) | p::before       | 在每个 <p> 元素之前插入内容。 |
| [::first-letter](https://www.w3school.com.cn/cssref/selector_first-letter.asp) | p::first-letter | 选择每个 <p> 元素的首字母。   |
| [::first-line](https://www.w3school.com.cn/cssref/selector_first-line.asp) | p::first-line   | 选择每个 <p> 元素的首行。     |
| [::selection](https://www.w3school.com.cn/cssref/selector_selection.asp) | p::selection    | 选择用户选择的元素部分。      |

## CSS不透明度

**opacity** **属性指定元素的不透明度/透明度。**

```js
img {
  opacity: 0.5;
}
```

## CSS导航栏

### 导航栏

易用的导航对于任何网站都很重要。

通过使用 CSS，您可以将无聊的 HTML 菜单转换为美观的导航栏。

**导航栏 = 链接列表**

导航栏需要标准 HTML 作为基础。

在我们的实例中，将用标准的 HTML 列表构建导航栏。

导航栏基本上就是链接列表，因此使用 <ul> 和 <li> 元素会很有意义：

```html
<ul>
  <li><a href="default.asp">Home</a></li>
  <li><a href="news.asp">News</a></li>
  <li><a href="contact.asp">Contact</a></li>
  <li><a href="about.asp">About</a></li>
</ul>
```

现在，从列表中删除项目符号以及外边距和内边距（填充）：

```html
ul {
  list-style-type: none;
  margin: 0;
  padding: 0;
}
```

- list-style-type: none; - 删除项目符号。导航条不需要列表项标记。
- 设置 margin: 0; 和 padding: 0; 删除浏览器的默认设置。

### 垂直导航栏

如需构建垂直导航栏，除了上一章中的代码外，还可以在列表中设置 <a> 元素的样式：

**实例**

```js
li a {
  display: block;
  width: 60px;
}
```

**例子解释：**

- `display: block`; - 将链接显示为块元素可以使整个链接区域都可以被单击（而不仅仅是文本），我们还可以指定宽度（如果需要，还可以指定内边距、外边距、高度等）。
- `width: 60px; `- 默认情况下，块元素会占用全部可用宽度。我们需要指定 60 像素的宽度。

您还可以设置 <ul> 的宽度，并删除 <a> 的宽度，因为当显示为块元素时，它们将占据可用的全部宽度。这将导致与我们之前的例子相同的结果：

```js
ul {
  list-style-type: none;
  margin: 0;
  padding: 0;
  width: 60px;
} 

li a {
  display: block;
}
```

### 全高固定垂直导航栏

创建全高的“粘性”侧面导航

即导航栏在某个位置不变

```js
ul {
  list-style-type: none;
  margin: 0;
  padding: 0;
  width: 25%;
  background-color: #f1f1f1;
  height: 100%; /* 全高 */
  position: fixed; /* 使它产生粘性，即使在滚动时 */
  overflow: auto; /* 如果侧栏的内容太多，则启用滚动条 */
}
```

### 设计点击样式

我们可以设置对应的点击效果

```js
li a.active {  /*被选中时候是该状态*/
  background-color: #4CAF50;
  color: white;
}

li a:hover:not(.active) {  /*没被选择而且没点击的时候*/
  background-color: #555;
  color: white;
}
```

### 水平导航栏

有两种创建水平导航栏的方法：使用*行内*或*浮动*列表项。

#### 行内列表项

构建水平导航栏的一种方法是，除了上一章中的“标准”代码外，还要将 <li> 元素指定为 inline：

```js
ul {
  list-style-type: none;
  margin: 0;
  padding: 0;
}

li {
  display: inline;
}
```

#### 浮动列表项

创建水平导航栏的另一种方法是浮动 <li> 元素，并为导航链接规定布局：

```js
li {
  float: left;
}

a {
  display: block;
  padding: 8px;
  background-color: #dddddd;
}
```

#### 右对齐链接

通过将列表项向右浮动来右对齐链接（float:right;）

```html
<ul>
  <li><a href="#home">Home</a></li>
  <li><a href="#news">News</a></li>
  <li><a href="#contact">Contact</a></li>
  <li style="float:right"><a class="active" href="#about">About</a></li>
</ul>
```

#### 边框分隔栏

```js
li {
  border-right: 1px solid #bbb;
}

li:last-child {
  border-right: none;
}
```

#### 固定的导航栏(重点)

固定在顶部

```html
ul {
  position: fixed;
  top: 0;
  width: 100%;
}
```

固定在底部

```html
ul {
  position: fixed;
  bottom: 0;
  width: 100%;
}
```

#### 灰色水平导航栏

```html
ul {
  border: 1px solid #e7e7e7;
  background-color: #f3f3f3;
}

li a {
  color: #666;
}
```

### 粘性导航栏

为 <ul> 添加 position: sticky;，以创建粘性导航栏。

粘性元素会根据滚动位置在相对和固定之间切换。它是相对定位的，直到在视口中遇到给定的偏移位置为止 - 然后将其“粘贴”在适当的位置（比如 position:fixed）。

```html
ul {
  position: -webkit-sticky; /* Safari */
  position: sticky;
  top: 0;
}
```

## CSS下拉菜单

基础

```html
<div class="dropdown">
  <span>Mouse over me</span>
  <div class="dropdown-content">
    <p>Hello World!</p>
  </div>
</div>
```

```html
<style>
.dropdown {   /*注意是在最外层的div中，不是bottom或者span，生成相对定位的元素，相对于其正常位置进行定位。*/
  position: relative;
  display: inline-block;
}

.dropdown-content {
  display: none;	/*是不显示的*/
  position: absolute;  /*生成绝对定位的元素，相对于 static 定位以外的第一个父元素进行定位。*/
  background-color: #f9f9f9;
  min-width: 160px;
  box-shadow: 0px 8px 16px 0px rgba(0,0,0,0.2);
  padding: 12px 16px;
  z-index: 1;
}

.dropdown:hover .dropdown-content {
  display: block;	/*设置显示*/
}
</style>
```

**HTML**

使用任何元素打开下拉菜单内容，例如 <span> 或 <button> 元素。

使用容器元素（如 <div>）创建下拉内容，并在其中添加任何内容。

用 <div> 元素包围这些元素，使用 CSS 正确定位下拉内容。

> 建议我们使用div来创建我们的下拉内容

**CSS**

`.dropdown` 类使用 `position:relative`，当我们希望将下拉内容放置在下拉按钮的正下方（使用 `position:absolute`）时，需要使用该类。

.dropdown-content 类保存实际的下拉菜单内容。默认情况下它是隐藏的，并将在悬停时显示（请看下文）。请注意，min-width 设置为 160px。可随时更改此设置。提示：如果您希望下拉内容的宽度与下拉按钮的宽度一样，请将宽度设置为 100％（设置 overflow:auto 可实现在小屏幕上滚动）。

我们用了 CSS box-shadow 属性，而不是边框，这样下拉菜单看起来像一张“卡片”。

当用户将鼠标移到下拉按钮上时，:hover 选择器用于显示下拉菜单。

### 下拉式菜单

```html
<div class="dropdown">
  <button class="dropbtn">Dropdown</button>
  <div class="dropdown-content">
  <a href="#">Link 1</a>
  <a href="#">Link 2</a>
  <a href="#">Link 3</a>
  </div>
</div>
```

```html
<style>
.dropbtn {
  background-color: #4CAF50;
  color: white;
  padding: 16px;
  font-size: 16px;
  border: none;
  cursor: pointer; /*光标形状，可设置或不设置*/
}

.dropdown {
  position: relative;
  display: inline-block;  /*设置在为内联块*/
}

.dropdown-content {
  display: none;
  position: absolute;
  background-color: #f9f9f9;
  min-width: 160px;
  box-shadow: 0px 8px 16px 0px rgba(0,0,0,0.2);
  z-index: 1;
}

.dropdown-content a {
  color: black;
  padding: 12px 16px;
  text-decoration: none;
  display: block;
}

.dropdown-content a:hover {
	background-color: #f1f1f1
}

.dropdown:hover .dropdown-content {
	display: block;
}

.dropdown:hover .dropbtn {
  background-color: #3e8e41;
}
</style>
```

### 下拉式导航

```html
<ul>
  <li><a href="#home">Home</a></li>
  <li><a href="#news">News</a></li>
  <li class="dropdown">
    <a href="javascript:void(0)" class="dropbtn">Dropdown</a>
    <div class="dropdown-content">  <!--在需要下拉导航的下面加入一个div-->
      <a href="#">Link 1</a>
      <a href="#">Link 2</a>
      <a href="#">Link 3</a>
    </div>
  </li>
</ul>
```

```html
<style>
ul {
  list-style-type: none;
  margin: 0;
  padding: 0;
  overflow: hidden;
  background-color: #333;
}

li {
  float: left;
}

li a, .dropbtn {
  display: inline-block;
  color: white;
  text-align: center;
  padding: 14px 16px;
  text-decoration: none;
}

li a:hover, .dropdown:hover .dropbtn {
  background-color: red;
}

li.dropdown {
  display: inline-block;
}

.dropdown-content {
  display: none;
  position: absolute;
  background-color: #f9f9f9;
  min-width: 160px;
  box-shadow: 0px 8px 16px 0px rgba(0,0,0,0.2);
  z-index: 1;
}

.dropdown-content a {
  color: black;
  padding: 12px 16px;
  text-decoration: none;
  display: block;
  text-align: left;
}

.dropdown-content a:hover {background-color: #f1f1f1;}

.dropdown:hover .dropdown-content {
  display: block;
}
</style>
```

## CSS表单输入

### 获得焦点的输入框

默认情况下，某些浏览器在获得焦点（单击）时会在输入框周围添加蓝色轮廓。您可以通过向输入添加 outline: none; 来消除此行为。

使用 :focus 选择器可以在输入字段获得焦点时为其设置样式：

```html
input[type=text]:focus {
  background-color: lightblue;
}
```

### 带有图标/图像的输入框

如果希望在输入框中包含图标，请使用 background-image 属性，并将其与 background-position 属性一起设置。还要注意，我们添加了一个较大的左内边距（padding-left）来留出图标的空间：

```html
input[type=text] {
  background-color: white;
  background-image: url('searchicon.png');
  background-position: 10px 10px; 
  background-repeat: no-repeat;
  padding-left: 40px;
}
```


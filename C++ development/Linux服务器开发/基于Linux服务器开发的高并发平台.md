





# `Linux`系统入门



操作系统一般分为个人操作系统和服务器操作系统。常见的个人操作系统有`window`、`mac`，服务器操作系统有`Linux`。`Linux`，是一种开源的类`UNIX`操作系统，是一个基于`POSIX`的多用户、多任务、支持多线程和多CPU的操作系统。

## 虚拟机

通过虚拟化技术，在电脑内，虚拟出计算机硬件，并给虚拟的硬件安装操作系统，即可得到一台虚拟的电脑，称之为虚拟机。



虚拟机的使用：

1. 克隆：首先需要关闭Linux系统，使用虚拟机的管理克隆即可。克隆分为软链接克隆和完全克隆。
2. 快照：虚拟机的快照，简单理解就是存档、读档。出现异常的时候可以利用快照管理快速回归前一个状态。



在学习Linux的时候，可在虚拟机上进行Linux的安装，也可以购买服务器，在服务器上部署Linux系统。这里介绍虚拟机下的安装：



1. 安装虚拟机，检查在网络适配器中检查是否有对应虚拟机的两个网络适配器

2. 下载CentOs操作系统

3. 新建虚拟机

4. 设置该虚拟机的CD/DVD，使用`Use IOS image file`方式启动

5. 启动安装，等待。

6. 选择语言，这里选择工作站模式安装，勾选兼容性、开发工具

7. 自定义三个区：`boot`引导分区、`swap`交换分区、根分区。前两者分别是1G、2G、剩下大小都是根分区的。交换分区相当于缓存，内存的扩展，除了swap分区文件系统都设置为ext4。

8. KDUMP在工作中是需要进行开启的。

9. 开启网络，选择NAT模式。桥接模式生产一个新的IP地址，可以让虚拟系统和其他外部IP地址主机进行通信，但占用数量本来就不多的IP地址，导致IP冲突。NAT模式可以产生一个新独立的、与主机非一个网段IP地址，虚拟机的网段和该IP地址网段一致，可以通过主机IP和其他IP地址主机通信。主机模式即一个独立系统。

10. 设置密码、用户、root。设置完成进行完成设置，最后点击火狐查看是否完成安装。

11. 安装 VMware Tools，在虚拟机VM选项下可直接安装。

    安装 VMware Tools是创建新的虚拟机过程的一部分，而升级 VMware Tools 是使虚拟机符合最新标准过程的一部分。尽管客户机操作系统在未安装 VMware Tools 的情况下仍可运行，但许多 VMware 功能只有在安装 VMware Tools 后才可用。安装 VMware Tools 以后，套件中的实用程序会提高虚拟机中客户机操作系统的性能和改善虚拟机管理。

    VMware Tools 安装程序是 ISO 映像文件。客户机操作系统中的 CD-ROM 会检测 ISO 映像文件。每种类型的客户机操作系统（包括 Windows、Linux 和 Mac OS X）具有一个 ISO 映像文件。在选择命令以安装或升级 VMware Tools 时，虚拟机的第一个虚拟 CD-ROM 磁盘驱动器暂时连接到客户机操作系统的 VMware Tools ISO 文件。

    如果使用的是 VMware Fusion、Workstation Player 或 Workstation Pro，您可以使用 Windows 简易安装或 Linux 简易安装功能在安装完操作系统后立即安装 VMware Tools。



![image-20240229233727658](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240229233727658.png)



复制到其他位置的计算机的opt里面。



![image-20240229233911719](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240229233911719.png)



1、打开终端，输入进入指令。

```shell
cd /opt 
```

2、解压XX文件，可以输入前几个字母后进行tab扩展，其中tar.gz为linux的压缩包。

```
tar -zxvf  XX //
```

3、解压文件后进入文件。

```
cd XX 
```

 4、ls命令用于列出文件和目录。

```
ls
```

5、解压文件

```
./ XX
```

最后一直回车即可。



![image-20240229235627683](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240229235627683.png)



此时安装完成，检查gcc是否已经安装，在终端输入命令。

```
gcc -v
```

![image-20240229235814091](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240229235814091.png)



检查完后建立共享文件夹，然后在设置中添加共享文件夹。



![image-20240301000015794](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240301000015794.png)



然后在虚拟机的mnt/hgfs里面即可找到刚刚添加的共享文件夹。



![image-20240301000253974](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240301000253974.png)



但是在实际的开发中，文件的上传和下载是需要使用远程方式完成。



## 目录结构

在 Linux 系统中，所有内容都是以文件的形式保存和管理的，即「一切皆文件」。普通文件是文件，目录（Windows 下称为文件夹）是文件，硬件设备（键盘、监视器、硬盘、打印机）是文件，就连套接字（socket）、网络通信等资源也都是文件。



linux只有一个根目录，而且文件和目录被组织成一个单根倒置树结构，此结构最上层是根目录，用“/”表示根文件系统(rootfs)：root filesystem 标准Linux文件系统（如：ext4）



![img](https://www.runoob.com/wp-content/uploads/2014/06/d0c50-linux2bfile2bsystem2bhierarchy.jpg)



以下是对这些目录的解释：

- **/bin**：bin 是 Binaries (二进制文件) 的缩写, 这个目录存放着最经常使用的命令。
  
- **/boot：**这里存放的是启动 Linux 时使用的一些核心文件，包括一些连接文件以及镜像文件。
  
- **/dev ：**dev 是 Device(设备) 的缩写, 该目录下存放的是 Linux 的外部设备，在 Linux 中访问设备的方式和访问文件的方式是相同的。
  
- **/etc：**etc 是 Etcetera(等等) 的缩写,这个目录用来存放所有的系统管理所需要的配置文件和子目录，比如安装mysql数据库my.conf。
  
- **/home**：用户的主目录，在 Linux 中，每个用户都有一个自己的目录，一般该目录名是以用户的账号命名的，如上图中的 alice、bob 和 eve。
  
- **/lib**：lib 是 Library(库) 的缩写这个目录里存放着系统最基本的动态连接共享库，其作用类似于 Windows 里的 DLL 文件。几乎所有的应用程序都需要用到这些共享库。
  
- **/lost+found**：这个目录一般情况下是空的，当系统非法关机后，这里就存放了一些文件。
  
- **/media**：linux 系统会自动识别一些设备，例如U盘、光驱等等，当识别后，Linux 会把识别的设备挂载到这个目录下。
  
- **/mnt**：系统提供该目录是为了让用户临时挂载别的文件系统的，我们可以将光驱挂载在 /mnt/ 上，然后进入该目录就可以查看光驱里的内容了。
  
- **/opt**：opt 是 optional(可选) 的缩写，这是给主机额外安装软件所摆放的目录。比如你安装一个ORACLE数据库则就可以放到这个目录下。默认是空的。
  
- **/proc**：proc 是 Processes(进程) 的缩写，/proc 是一种伪文件系统（也即虚拟文件系统），存储的是当前内核运行状态的一系列特殊文件，这个目录是一个虚拟的目录，它是系统内存的映射，我们可以通过直接访问这个目录来获取系统信息。
  这个目录的内容不在硬盘上而是在内存里，我们也可以直接修改里面的某些文件，比如可以通过下面的命令来屏蔽主机的ping命令，使别人无法ping你的机器：
  
  ```
  echo 1 > /proc/sys/net/ipv4/icmp_echo_ignore_all
  ```
  
- **/root**：该目录为系统管理员，也称作超级权限者的用户主目录。
  
- **/sbin**：s 就是 Super User 的意思，是 Superuser Binaries (超级用户的二进制文件) 的缩写，这里存放的是系统管理员使用的系统管理程序。
  
- **/selinux**：这个目录是 Redhat/CentOS 所特有的目录，Selinux 是一个安全机制，类似于 windows 的防火墙，但是这套机制比较复杂，这个目录就是存放selinux相关的文件的。
  
- **/srv**：该目录存放一些服务启动之后需要提取的数据。
  
- **/sys**：这是 Linux2.6 内核的一个很大的变化。该目录下安装了 2.6 内核中新出现的一个文件系统 sysfs 。

  sysfs 文件系统集成了下面3种文件系统的信息：针对进程信息的 proc 文件系统、针对设备的 devfs 文件系统以及针对伪终端的 devpts 文件系统。

  该文件系统是内核设备树的一个直观反映。

  当一个内核对象被创建的时候，对应的文件和目录也在内核对象子系统中被创建。

- **/tmp**：tmp 是 temporary(临时) 的缩写这个目录是用来存放一些临时文件的。
  
- **/usr**：usr 是 unix shared resources(共享资源) 的缩写，这是一个非常重要的目录，用户的很多应用程序和文件都放在这个目录下，类似于 windows 下的 program files 目录。
  
- **/usr/bin：**系统用户使用的应用程序。
  
- **/usr/sbin：**超级用户使用的比较高级的管理程序和系统守护程序。
  
- **/usr/src：**内核源代码默认的放置目录。
  
- **/var**：var 是 variable(变量) 的缩写，这个目录中存放着在不断扩充着的东西，我们习惯将那些经常被修改的目录放在这个目录下。包括各种日志文件。
  
- **/run**：是一个临时文件系统，存储系统启动以来的信息。当系统重启时，这个目录下的文件应该被删掉或清除。如果你的系统上有 /var/run 目录，应该让它指向 run。

## 远程登陆

公司开发项目的时候，具体的应用场景是这样的：

- linux服务器是开发小组共享
- 正式上线的项目是运行在公网
- 因此程序员需要远程登录到Linux进行项目管理或者开发
- 画出简单的网络拓扑示意国(帮助理解)

远程登录客户端有Xshell6， Xftp6，我们学习使用Xshell和Xftp6，其它的远程工具大同小异。



想要远程连接，必须知道Linux系统的IP地址。在系统中输入指令`ifconfig`，找到ens33设备的`inet`即其IP地址。在本地的`cmd`窗口`ping`检查本地是否连通。找到对应IP后即可通过Xshell6， Xftp6建立连接。Xftp登陆后把编码修正为UTF-8，否则可能会发生乱码。



这个时候就可以上传/下载文件了。



## 文本编辑器



所有的 Unix Like 系统都会内建 vi 文书编辑器，其他的文书编辑器则不一定会存在。但是目前我们使用比较多的是 vim 编辑器。vim 具有程序编辑的能力，可以主动的以字体颜色辨别语法的正确性，方便程序设计。



基本上 vi/vim 共分为三种模式，命令模式（Command Mode）、输入模式（Insert Mode）和命令行模式（Command-Line Mode）。



一、命令模式



用户刚刚使用`vim`，便进入了命令模式。此状态下敲击键盘动作会被 Vim 识别为命令，而非输入字符，比如我们此时按下 **i**，并不会输入一个字符，**i** 被当作了一个命令。



以下是普通模式常用的几个命令：

- **i** -- 切换到输入模式，在光标当前位置开始输入文本。
- **x** -- 删除当前光标所在处的字符。
- **:** -- 切换到底线命令模式，以在最底一行输入命令。
- **a** -- 进入插入模式，在光标下一个位置开始输入文本。
- **o**：在当前行的下方插入一个新行，并进入插入模式。
- **O** -- 在当前行的上方插入一个新行，并进入插入模式。
- **dd** -- 剪切当前行，剪切当前行向下n行，对应ndd。
- **yy** -- 复制当前行，复制当前行向下n行，对应nyy。
- **p**（小写） -- 粘贴剪贴板内容到光标下方。
- **P**（大写）-- 粘贴剪贴板内容到光标上方。
- **u** -- 撤销上一次操作。
- **Ctrl + r** -- 重做上一次撤销的操作。
- **:w** -- 保存文件。
- **:q** -- 退出 Vim 编辑器。
- **:q!** -- 强制退出Vim 编辑器，不保存修改。
- **G/gg** -- 定位尾行、首行。
- **n shift+g**  -- 快速定位n行。

若想要编辑文本，只需要启动 Vim，进入了命令模式，按下 **i** 切换到输入模式即可。命令模式只有一些最基本的命令，因此仍要依靠**底线命令行模式**输入更多命令。



二、输入模式



在命令模式下按下 **i** 就进入了输入模式，使用 **Esc** 键可以返回到普通模式。



在输入模式中，可以使用以下按键：

- **字符按键以及Shift组合**，输入字符
- **ENTER**，回车键，换行
- **BACK SPACE**，退格键，删除光标前一个字符
- **DEL**，删除键，删除光标后一个字符
- **方向键**，在文本中移动光标
- **HOME**/**END**，移动光标到行首/行尾
- **Page Up**/**Page Down**，上/下翻页
- **Insert**，切换光标为输入/替换模式，光标将变成竖线/下划线
- **ESC**，退出输入模式，切换到命令模式



三、底线命令模式



在命令模式下按下 **:**（英文冒号）就进入了底线命令模式。底线命令模式可以输入单个或多个字符的命令，可用的命令非常多。

在底线命令模式中，基本的命令有（已经省略了冒号）：

- `:w`：保存文件。
- `:q`：退出 Vim 编辑器。
- `:wq`：保存文件并退出 Vim 编辑器。
- `:q!`：强制退出Vim编辑器，不保存修改。
- `/key`: 查找关键字，可查多个一次返回一次，想查找另一个时候在输入`/`即可。
- `:set nu`和`:set nonu`: 查看行号与取消行号。
- `:e`：刷新

按 **ESC** 键可随时退出底线命令模式。



## 常用指令

一 、用户管理



1. 登录/切换注销：`su username`。登录的时候少用管理员进行登录，避免操作失误。利用普通用户登录后使用以下命令转化为管理员身份。

2. 注销用户：`logout`。但在图像界面运行的时候无效，在运行级别三下才有效。

3. 添加用户：`useradd username`。当需要使用Linux系统的时候，需要想系统管理员申请一个账号，管理员使用以下命令。默认生成的用户`home`目录在`/home/name`(所有用户都在`/home`目录中)，假设要自定义目录`/route`下生成，则命令如下`useradd -d /route username`。

4. 设置密码：`passwd username`

5. 移除用户：`userdel username/userdel -r username`。删除分为保存家目录和不保存家目录，对应前后两句`shell`语句。

6. 查询用户：`id username`

7. 查看当前用户：`who am i`。只显示第一个登陆的账号，切换用户的时候还是显示原用户

   

二、用户分组



1. 新增组：`groupadd groupname`
2. 删除组：`groupdel groupname`
3. 增加用户并分配组：`useradd -g groupname username`。当添加新用户的时候没有指定组，则会生成一个组，把该用户放入。
4. 移动用户到某个组：`usermod -g groupname username`



用户和组相关文件：

- `/etc/passwd`文件：用户 （user）的配置文件，记录用户的各种信息。每行的含义:用户名:口令:用户标识号(uid):组标识号(gid):注释性描述:主目录:登录Shell(命令行和内核之间有一个翻译官shell，一般国内使用bashall)
- `/etc/shadow`文件：口令的配置文件。每行的含义:登录名:加密口令:最后一次修改时间:最小时间间隔:最大时间间隔:警告时间:不活动时间:失效时间:标志。
- `/etc/group`文件：组(group)的配置文件，记录Linux包含的组的信息每行含义:组名:口令:组标识号:组内用户列表。
  ·



三、运行级别



Linux系统7个运行级别，这个级别从0到6 ，具有不同的功能。



级别具体说明：

- 0： 系统停机（关机）模式，系统默认运行级别不能设置为0，否则不能正常启动，一开机就自动关机。
- 1：单用户模式，root权限，用于系统维护，禁止远程登陆，就像Windows下的安全模式登录。
- 2：多用户模式，没有NFS网络支持。
- 3：完整的多用户文本模式，有NFS，登陆后进入控制台命令行模式。（工作一般模式）
- 4：系统未使用，保留一般不用，在一些特殊情况下可以用它来做一些事情。例如在笔记本电脑的电池用尽时，可以切换到这个模式来做一些设置。
- 5：图形化模式，登陆后进入图形GUI模式或GNOME、KDE图形化界面，如X Window系统。
- 6：重启模式，默认运行级别不能设为6，否则不能正常启动，就会一直开机重启开机重启。



1. 设置运行级别n：`init n`
2. 查看当前级别：`systemctl get-default`
3. 修改默认级别为其他grade(对应名称)级别:`systemctl set-default grade.target`。注意参数需要进行查表找到对应的`grade.target`



四、Linux开机开机、重启



1. 立即关机：`shutdown -h now`
2. n分钟后关机：`shutdown -h n`。参数为空的时候默认1min。
3. 立即重启：`reboot`
4. 关机：`halt`
5. 数据同步：`synu`。把内存的数据同步到磁盘，无论是重启还是关闭系统，首先都要运行该指令，以上指令都在关机前自动运行。



五、常用指令



1.  显示文件或目录：`ls`。参数`-l`，列出文件详细信息(list)，参数`-a`列出当前目录下所有文件及目录，包括隐藏的(all)。
2. 创建目录：`mkdir`。参数`-p`，创建目录，若无父目录，则创建p(parent)。
3. 切换目录：`cd`。无参数的情况下返回根目录。
4. 创建空文件：`touch`
5. 查看文件内容：`cat`　      
6. 拷贝：`cp` 
7. 移动或删除重命名：`mv`
8. 删除文件：`rm`。参数`-r`，递归删除，可删除子目录及文件，参数`-f`，强制删除。
9. 在文件系统中搜索某文件：`find`
10. 显示当前目录路径：`pwd`
11. 树形显示目录：`tree`
12. 查看环境变量：`env`



wc                统计文本中行数、字数、字符数

grep             在文本文件中查找某个字符串

rmdir           删除空目录

ln                  创建链接文件

more、less  分页显示文本文件内容

head、tail    显示文件头、尾内容

ctrl+alt+F1  命令行全屏模式

软连接 	In -s filename1 filename2

ls -l



## 找回root密码

root 作为系统最高权限管理者，它的密码自然是至关重要的，那么 root 账户的密码应该怎么找回呢？步骤如下：



1. 启动 Linux 系统，待进入开机界面后按 “e” 进入编辑界面，注意此处要快，在系统进入登录页面之前进行操作；

![image.png](https://ucc.alicdn.com/pic/developer-ecology/7dce4599820a4ed7a5a32df9b7f0e36c.png)



2. 进入编辑界面后，找到以“Linux 16 ”开头的内容所在行，并在行最后输入 init=/bin/sh；

![image.png](https://ucc.alicdn.com/pic/developer-ecology/806851e2567b4b7da8e04632389a3bb7.png)



3. 输入完成后，按下 Ctrl+X 进入单用户模式，如下界面即为单用户模式；

![image.png](https://ucc.alicdn.com/pic/developer-ecology/70cab81ee978415db5ed5f35c5611124.png)



4. 在光标闪烁的位置输入 mount -o remount,rw /，输入完成后回车；

![image.png](https://ucc.alicdn.com/pic/developer-ecology/c6549ec9ab974c3ab248226a304f3ab4.png)



5. 在新的行末输入 passwd 并回车，接下来输入密码、确认密码即可，修改密码成功后显示 passwd... 字样；

![image.png](https://ucc.alicdn.com/pic/developer-ecology/f913b6c3c170435db8b2007adc4ec9af.png)



6. 接下来在新的行末输入 touch /.autorelabel，输入完成回车；



7. 新的行末继续输入 exec /sbin/init，完成后回车等待系统修改密码；

![image.png](https://ucc.alicdn.com/pic/developer-ecology/79116d05eee84ecd94f4f688c0529ed6.png)



8. 耐心等待，系统自动重启后新的 root 密码即可生效。

## 帮助指令



清空屏幕 ctrl l

环境变量 env

配置环境变量 export envname = $envname:newenvname

查看环境变量 echo $envname

ps aux

ps ajx

ulimit -a 根据提示可以增加ulimit - 符号 

./执行文件 >> a.txt

./执行文件 & 以后台

netstat -anp 查看网络相关的命令

​	-a所有的socket
​	-p显示正在使用socket的程序的名称

​	-n直接使用IP地址，而不通过域名服务器

# Linux系统编程入门

## `Gcc`介绍

`Gcc`（[GNU](https://baike.baidu.com/item/GNU/671972?fromModule=lemma_inlink) Compiler Collection，[GNU编译器](https://baike.baidu.com/item/GNU编译器/10444865?fromModule=lemma_inlink)套件）是由GNU开发的编程语言编译器。GNU编译器套件包括C、C++、 [Objective-C](https://baike.baidu.com/item/Objective-C/8374012?fromModule=lemma_inlink)、 [Fortran](https://baike.baidu.com/item/Fortran/674319?fromModule=lemma_inlink)、[Java](https://baike.baidu.com/item/Java/85979?fromModule=lemma_inlink)、[Ada](https://baike.baidu.com/item/Ada/5606819?fromModule=lemma_inlink)和[Go](https://baike.baidu.com/item/Go/953521?fromModule=lemma_inlink)语言前端，也包括了这些语言的库（如`ibstdc++`，`libgcj`等。）



`Gcc`不仅支持C的许多"方言"，也可以区别不同的C语言标准；可以使用命令行选项来控制编译器在翻译源代码时应该遵循哪个C标准。例如，当使用命令行参数`-std=c99`启动`Gcc`时，编译器支持C99标准。



下面进行GCC工作流程的介绍：

1. 在进行源代码编写后得到文件`.c/.h/.cpp`。
2. 经过预处理器处理得到预处理后的源代码`.i`。
3. 经过编译器处理得到汇编语言`.s`。
4. 经过汇编器处理得到目标代码，和其他代码在链接器进行合并。
5. 经过链接器得到可执行文件`.exe/.out`

| gcc编译选项  | 说明                                                         |
| ------------ | ------------------------------------------------------------ |
| -E           | 预处理但不编译                                               |
| -S           | 编译但不汇编                                                 |
| -c           | 编译、汇编但不链接                                           |
| -o           | 把`file1`编译成可执行`file2`                                 |
| -g           | 编译的时候生产调试信息                                       |
| -I directory | 指定include包含文件的搜索目录，即头文件不在`main`函数同级目录中则可根据相对路径来指定 |
| -D           | 编译的时候指定一个宏（调试）                                 |
| -w           | 不生成警告信息                                               |
| -Wall        | 生成所有的警告信息                                           |
| -On          | 生产n，取值范围：0~3，对应编译器的优化的四个级别             |
| -l           | 编译的时候指定使用库，即指定库文件，注意这里参数是库的名称   |
| -L           | 编译的时候指定搜索的库的路径，即库文件不在`main`函数同级目录中则可根据相对路径来指定，注意这里参数是库的名称 |
| -fPIC/fpic   | 生成与位置无关的代码                                         |
| -share       | 生成共享目标文件，通常用于建立共享库                         |
| -std         | 指定C方言，如:`-std=c99`，gcc默认方言为GUN C                 |

当执行后面命令时候会自动完成前面的命令。同时，一些常用的指令如下：



1. 安装命令：`sudo apt install gcc g++`
2. 查看版本号：`gcc/g++ -v/--version`
3. 创建文件：`touch file1.c` 
4. 编译文件：`gcc file1.c -o file2/gcc -o file2 file1.c`
5. 运行程序：`./file2`



gcc 和g++都是GNU(组织)的一个编译器。



**误区一：gcc只能编译c代码, g++只能编译c++代码。**两者都可以，请注意:

1. 后缀为`.c`的，gcc 把它当作是C程序，而g++当作是 c++程序。
2. 后缀为`.cpp` 的，两者都会认为是C++程序，C++的语法规则更加严谨。
3. 编译阶段， g++会调用gcc，对于C++代码，两者是等价的，但是因为gcc命令不能自动和C++程序使用的库联接，所以通常用g++来完成链接， 为了统一起见，干脆编译/链接都用g++了，这就给人一种错觉，好像cpp程序只能用g++似的。



**误区二：gcc 不会定义_cplusplus 宏，而g++会。**实际上：

1. 这个宏只是标志着编译器将会把代码按C还是C++语法来解释。

2. 如上所述，如果后缀为.c，并且采用gcc编译器，则该宏就是未定义的，否则，就是已定义。



**误区三:编译只能用gcc，链接只能用g++。** 实际上：

1. 严格来说，这句话不算错误，但是它混淆了概念，应该这样说：编译可以用`gcc/g++`，而链接可以用`g++`或者`gcc -lstdc++`。
2. gcc命令不能自动和c++程序使用的库联接，所以通常使用g++来完成联接。但在编译阶段, g++会自动调用gcc，二者等价。

## 库文件

库文件是计算机上的一类文件，可以简单的把库文件看成―种代码仓库，它提供给使用者一些可以直接拿来用的变量、函数或类。



库是特殊的一种程序，编写库的程序和编写一般的程序区别不大，只是库不能单独运行。库文件有两种，



静态库和动态库（共享库)区别是∶静态库在程序的链接阶段被复制到了程序中；动态库在链接阶段没有被复制到程序中，而是程序在运行时由系统动态加载到内存中供程序调用。



库的好处:

1. 代码保密
2. 方便部署和分发



静态库在GCC进行链接时，会把静态库中代码打包到可执行程序中。而在动态库 GCC进行链接时，动态库的代码不会被打包到可执行程序中。



假如需要使用动态库，需要程序启动之后，动态库会被动态加载到内存中，通过`ldd filename`(list dynamicdependencies）命令检查动态库依赖关系。



如何定位共享库文件呢:

1. 当系统加载可执行代码时候，能够知道其所依赖的库的名字，但是还需要知道绝对路径。此时就需要系统的动态载入器来获取该绝对路径。
2. 对于elf格式的可执行程序，是由`ld-linux.so`来完成的，它先后搜索elf文件的`DT_RPATH`段（程序在运行时候是一个进程，操作系统会为其分配虚拟内存空间，该字段存虚拟内存空间中，不可修改）—>环境变量`LD_LIBRARY_PATH`（招不到的时候找环境变量）—>`/etc/ld.so.cache`文件列表（还找不到的时候找该文件列表）—>`/lib/`，`/usr/lib`目录找到库文件后将其载入内存（最后找不到该目录中找）。

## 静态库和动态库

**对于静态库来说，不同操作系统命名规则不同：**

1. Linux：`libfilename.a`
2. window： `libfilename.lib`

在Linux系统下的静态库制作：

1. 将需要进行静态库制作的程序放在一个目录下，进入该目录
2. 使用`gcc -c file1.c file2.c` 获得对应的`.o`文件
3. 把`.o`文件打包，使用ar工具（archive），使用命令`ar rcs libfilename.a file1.o file2.o`，其中r、c、s 分别代表将文件插入备存文件，建立备存文件，建立索引

指定好对应静态库后：

1. 使用`cp`指令把静态库导入项目的`lib`下
2. 编译的时候利用gcc命令中的指令把头文件`include`、库`lib`的路径进行设定



**对于动态库来说，不同操作系统命名规则不同：**

1. Linux：`libfilename.so`
2. window： `libfilename.ddl`

在Linux系统下的动态库制作：

1. 将需要进行静态库制作的程序放在一个目录下，进入该目录
2. 使用`gcc -c -fpic/-fPIC file1.c file2.c` 获得对应的`.o`文件
3. 把`.o`文件打包，得到动态库`gcc -shared file1.o file2.0 -o libfilename.so`

指定好对应动态库后：

1. 使用`cp`指令把静态库导入项目的`lib`下

2. 编译的时候利用gcc命令中的指令把头文件`include`、库`lib`的路径进行设定

3. 假设运行的时候动态库链接失败：

   - 终端配置（临时，关于环境变量`LD_LIBRARY_PATH`配置：）：
     - 执行命令`export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:newLD_LIBRARY_PATH`
     - 检查是否添加成功`echo $LD_LIBRARY_PATH`
     - 再使用`ldd filename`进行查看对应动态库链接
     - 运行
   - 用户级别配置（永久，关于环境变量`LD_LIBRARY_PATH`配置：）:
     - 使用`cd`进入根目录，`vim .bashrc` ，在尾部添加`export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:newLD_LIBRARY_PATH`
     - 使用`./source .bashrc`使配置生效
     - 检查是否添加成功`echo $LD_LIBRARY_PATH`
     - 再使用`ldd filename`进行查看对应动态库链接
     - 运行

   - 系统级别配置（永久）：
     - 关于环境变量`LD_LIBRARY_PATH`配置：
       - 使用`cd`进入根目录，`vim /etc/profile` ，在尾部添加`export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:newLD_LIBRARY_PATH`
       - 使用`./source /etc/profile`使配置生效
       - 检查是否添加成功`echo $LD_LIBRARY_PATH`
       - 再使用`ldd filename`进行查看对应动态库链接
       - 运行
     - 关于`/etc/ld.so.cache`文件列表配置：
       - 使用`cd`进入根目录，`vim /etc/conf` ，添加`newLD_LIBRARY_PATH`
       - 使用`sudo ldconfig`使配置生效
       - 再使用`ldd filename`进行查看对应动态库链接
       - 运行



动/静态库对比：无论是静态库还是动态库，都是在链接阶段才进行处理。静态库、动态库区别来自链接阶段如何处理，链接成可执行程序。分别称为静态链接方式和动态链接方式。

|        | 优点                               | 缺点                           |
| ------ | ---------------------------------- | ------------------------------ |
| 静态库 | 静态库被打包到应用程序中加载速度快 | 消耗系统资源,浪费内存          |
|        | 发布程序无需提供静态库，移植方便   | 更新、部署、发布麻烦           |
| 动态库 | 可以实现进程间资源共享（共享库)    | 加载速度比静态库慢             |
|        | 更新、部署、发布简单               | 发布程序时需要提供依赖的动态库 |
|        | 可以控制何时加载动态库             |                                |

## ``Makefile``介绍



一个工程中的源文件不计其数，其按类型、功能、模块分别放在若干个目录中，通过在不同索引下进行查找对应的文件，更利于维护。`Makefile`文件定义了一系列的规则来指定哪些文件需要先编译，哪些文件需要后编译，哪些文件需要重新编译，甚至于进行更复杂的功能操作，因为`Makefile` 文件就像一个shell脚本一样， 也可以执行操作系统的命令。



大量的源文件不可能手动进行输入命令进行编译，而且编译或许需要要求优先级，`Makefile`带来的好处就是"自动化编译”，一旦写好，只需要一个`make`命令，整个工程完全自动编译，极大的提高了软件开发的效率。`make` 是一个命令工具，是一个解释 `Makefile` 文件中指令的命令工具，一般来说，大多数的IDE都有这个命令，比如Delphi 的`make`， Visual C++的`nmake`，Linux下GNU的`make`。



文件命名：`Makefile` 或者`Makefile`



一个`Makefile` 文件中可以有一个或者多个规则。目标即最终要生成的文件(伪目标除外)，依赖即生成目标所需要的文件或是目标，命令:即通过执行命令对依赖操作生成目标（命令前必须Tab缩进)。形式如下：

```
目标...：依赖...
	命令(she11命令)
	...
```

这样写方便的原因，是因为这些依赖的文件假如发生了改变，则需要重新编译，而使用这个工具后，输入指令`make`即可马上完成编译工作，不需要进行再进行一次`gcc`。



下面介绍其工作原理。



`Makefile`文件的其他规则都是为第一条规则服务。假如是不属于第一条规则的依赖对应的规则，是不会执行的。



命令在执行之前，需要先检查规则中的依赖是否存在：

1. 如果存在，执行命令
2. 如果不存在，向下检查其它的规则，检查有没有一个规则是用来生成这个依赖的。如果找到了，则执行该规则中的命令。当生产对应的目标后，再递归执行原命令



检测更新。在执行规则中的命令时，会比较目标和依赖文件的时间（相当缓存机制，依赖文件不变时候，目标文件不变）：

1. 如果依赖的时间比目标的时间晚，需要重新生成目标
2. 如果依赖的时间比目标的时间早，目标不需要更新，对应规则中的命令不需要被执行



```shell
app:sub.c add.c mult.c div.c main.c
        gcc sub.c add.c mult.c div.c main.c -o app
```

```shell
app:sub.o add.o mult.o div.o main.o
        gcc sub.o add.o mult.o div.o main.o -o app

sub.o:sub.c
                gcc -c sub.c -o sub.o

add.o:add.c
                gcc -c add.c -o add.o

mult.o:mult.c
                gcc -c mult.c -o mult.o

div.o:div.c
                gcc -c div.c -o div.o

main.o:main.c
                gcc -c main.c -o main.o

```

建议以下面的写法为主，耦合性更低。



下面介绍其遍历。



自定义变量：变量名=变量值，例如var=hello



预定义变量：

1. AR ：归档维护程序的名称，默认值为ar
2. CC : c编译器的名称，默认值为cc
3. CXX : C++编译器的名称，默认值为g++
4. $@ ：目标的完整名称
5. $<：第一个依赖文件的名称
6. $^：所有的依赖文件

其中4 5 6均只能在`shell`使用



获取变量的值：$(变量名)，例如$(var)

```shell
app:main.c a.c b.c
	gcc -c main.c a.c b.c
```

可以使用变量修改为

```shell
app:main.c a.c b.c
	$(CC) -c $^ -o $@
```

则刚刚的文件可修改为

```shell
src=sub.o add.o mult.o div.o main.o
target=app
$(target):$(src)
        $(CC) $(src) -o $(target)

sub.o:sub.c
                gcc -c sub.c -o sub.o

add.o:add.c
                gcc -c add.c -o add.o

mult.o:mult.c
                gcc -c mult.c -o mult.o

div.o:div.c
                gcc -c div.c -o div.o

main.o:main.c
                gcc -c main.c -o main.o

```

下面介绍模式匹配。



利用通配符进行匹配：



`%.o:%.c`：其中，`%`是通配符，匹配一个字符串，而两个`%`匹配同一个字符串

```shell
src=sub.o add.o mult.o div.o main.o
target=app
$(target):$(src)
        $(CC) $(src) -o $(target)

%.o:%.c
        $(CC) -c $< -o $@ 
```



`Makefile`函数的介绍如下。



1、获取`.c`文件

`$ (wildcard PATTERN...)`，其中`wildcard`为函数，`PATTERN`为参数：

1. 功能：获取指定目录下指定类型的文件列表
2. 参数: PATTERN指的是某个或多个目录下的对应的某种类型的文件，如果有多个目录，一般使用空格间隔
3. 返回:得到的若干个文件的文件列表，文件名之间使用空格间隔
4. 示例:
   `$ ( wildcard *.c ./ sub/*.c)`获取当前目录下的`*.c`和当前目录下的sub文件夹的`*.c`，则返回值格式: a.c b.c c.c d.c e.c f.c



2、获取`.o`文件

`$(patsubst <pattern> ,<replacement>,<text>)`，其中`patsubst`为函数，剩余为参数：

1. 功能：查找<text>中的单词（单词以"空格"、“Tab"或"回车""换行"分隔）是否符合模式<pattern>，如果匹配的话，则以<replacement>替换。

2. <pattern>可以包括通配符`%`，表示任意长度的字串。如果<replacement>中也包含`%`，那么，<replacement>中的这个`%`将是<pattern>中的那个号所代表的字串。(可以用`l`来转义，以`\%`来表示真实含义的`%`字符)

3. 返回：函数返回被替换过后的字符串

4. 示例:
   `$(patsubst %.c,%.o,x.c bar.c)`

   返回值格式:`x.o` 、`bar.o`



3、删除多余文件

使用`clean`规则把对应的文件进行删除，但是执行该规则需要使用`make clean`命令。

```shell
src=$(wildcard ./*.c)
objs=$(patsubst %.c,%.o,$(src))
target=app
$(target):$(objs)
        $(CC) $(objs) -o $(target)

%.o:%.c
        $(CC) -c $< -o $@ 
.PHONY:clean
clean:
        rm $(objs) -f
```

要求规则名不允许和原目录下的任何文件同名，不然需要加上`.PHONY:clean`表示尾目标，不会生成特定的文件。



## GDB介绍



GDB是由GNU软件系统社区提供的调试工具，同GCC配套组成了一套完整的开发环境，GDB 是Linux和许多类unix系统中的标准开发环境。



一般来说, GDB主要帮助你完成下面四个方面的功能：

1. 启动程序，可以按照自定义的要求随心所欲的运行程序
2. 可让被调试的程序在所指定的调置的断点处停住（断点可以是条件表达式)
3. 当程序被停住时，可以检查此时程序中所发生的事
4. 可以改变程序，将一个 BUG产生的影响修正从而测试其他 BUG



通常，在为调试而编译时，我们会关掉编译器的优化选项（`-o`) ，并打开调试选项(`-g`)。另外，`-wall`在尽量不影响程序行为的情况下选项打开所有warning，也可以发现许多问题，避免一些不必要的BUG。



`gcc -g -wall program.c -o program`



`-g`选项的作用是在可执行文件中加入源代码的信息，比如可执行文件中第几条机器指令对应源代码的第几行，但并不是把整个源文件嵌入到可执行文件中，所以在调试时必须保证gdb能找到源文件`*.c`。



常用的断点命令如下：

1. `gbd filename`：对文件进入gbd模式（shell）
2. `q`：退出gbd模式
3. `set args argsvalue`：给`main`函数设置参数
4. `show args`：显示参数
5. `help`：显示帮助手册
6. 查看当前文件代码：
   - `list/l args`：一次可查看10行，可按回车继续显示（默认执行上一条命令），`args`可以是函数/行号，显示以`args`为中心的上下10行
   - 远程连接vscode
7. 查看非当前文件代码：
   - `list/l filename:args`：一次可查看10行，可按回车继续显示（默认执行上一条命令），`args`可以是函数/行号，显示以`args`为中心的上下10行
8. `set list value`：设置行号
9. `show list`：显示行号
10. `b/break args`：对于当前文件进行打断点，其中`args`可以是函数/行号，显示以`args`为中心的上下10行
11. `b/break filename:args`：对于当前文件进行打断点，其中`args`可以是函数/行号，显示以`args`为中心的上下10行
12. `info/i break/b`：查看断点信息
13. `d/del/delete breakNum`：删除断点，参数为其编号
14. `dis/disable breakNum`：设置断点无效
15. `ena/enable breakNum`：设置断点生效
16. `b/break 10 if i==5`：设置条件断点（一般在循环位置设置）



常用的调试命令如下：

1. `start`：运行gdb程序，停在第一行
2. `run`：运行gdb程序，停在第一个断点
3. `c/continue`：运行到下一个断点
4. `n/next`：向下执行一行代码（不进入函数体，直接调用执行完该函数）
5. `s/step`：向下单步调试（进入函数体）
6. `finish`：跳出函数体
7. `p/print args`：打印变量名（值）
8. `ptype args` ：打印变量名（类型）
9. `until`：跳出循环（循环中不允许有断点，否则无法退出）
10. `display args`：自动变量操作，自动打印指定变量的值，即反复执行该变量的值
11. `undisplay args`：自动变量操作，取消自动打印指定变量的值
12. `i/info display`：显示自动变量信息
13. `set var args=value`：改变变量的值
14. `core-file core`：查看`core`文件（错误信息，调试）



## 文件I/O



I/O就是文件内容与内存信息的交换，即从文件中读取到内存，从内存写到内存中。



在标准的C库IO函数的可以跨平台（不同操作系统都可以运行，这里是使用不同系统的API进行），Qt、Java（虚拟机形式）也可以跨平台。



标准C库I/O函数效率显然高于Linux系统的I/O函数，在网络通信的时候使用Linux系统的I/O函数。



利用标准C库I/O函数调用系统中的`fopen`的API，返回一个`FILE *fp`，而`FILE`为一个结构体：文件描述符、文件的读写指针、I/O缓冲区（内存地址）。



其中有缓冲区(`buffer`)，在以下情况把缓冲区(8K大小左右)刷新到磁盘：

1. `fflush`
2. 缓冲区满
3. 正常关闭文件
   - flose
   - return(main函数)
   - exit(main函数)



但Linux的I/O函数是没有缓冲区的（网络通信需要效率）且`open`返回的是一个文件描述符，根据需求进行不同I/O库的使用。



使用C标准I/O库进行读写进缓冲区然后调用Linux内核一次性写入磁盘。





来简单看一下`FILE`结构体：

```c
#ifndef __FILE_defined
#define __FILE_defined 1

struct _IO_FILE;

/* The opaque type of streams.  This is the definition used elsewhere.  */
typedef struct _IO_FILE FILE;

#endif

```

```c
struct _IO_FILE
{
  int _flags;		/* High-order word is _IO_MAGIC; rest is flags. */

  /* The following pointers correspond to the C++ streambuf protocol. */
  char *_IO_read_ptr;	/* Current read pointer */
  char *_IO_read_end;	/* End of get area. */
  char *_IO_read_base;	/* Start of putback+get area. */
  char *_IO_write_base;	/* Start of put area. */
  char *_IO_write_ptr;	/* Current put pointer. */
  char *_IO_write_end;	/* End of put area. */
  char *_IO_buf_base;	/* Start of reserve area. */
  char *_IO_buf_end;	/* End of reserve area. */

  /* The following fields are used to support backing up and undo. */
  char *_IO_save_base; /* Pointer to start of non-current get area. */
  char *_IO_backup_base;  /* Pointer to first valid character of backup area */
  char *_IO_save_end; /* Pointer to end of non-current get area. */
  
  int _fileno;//文件描述符
  //....
}
```



下面介绍虚拟地址空间。



程序（可执行文件，在磁盘中）运行起来变成进程的时候才会生产对于的虚拟地址空间，用于解决内存的问题，虚拟地址的空间的大小由CPU决定。比如32位机器对应的虚拟地址空间就是2<sup>32</sup>，64位的机器对应的虚拟地址空间就是2<sup>48</sup>。



这里以32位机器介绍虚拟地址空间（大小为4G）：

1. 其中0-3G为用户区，剩下的1G属于内核区
2. 虚拟地址空间由CPU中的MMU映射到真实的物理内存当中（转换），但实际上是不会占物理内存的4G
3. 用户区(低地址往高地址)
   - 受保护的地址（0-4k）
   - `.text`：代码段，二进制机械指令），为ELF
   - `.data`：已经初始化的全局变量，为ELF
   - `.bss`：未初始化的全局变量，为ELF
   - 堆空间（比栈空间大，低地址往高地址）
   - 共享库
   - 栈空间（高地址往低地址）
   - 命令行参数（函数的参数传递）
   - 环境变量（Linux环境变量）
4. 内核区
   - 内存管理
   - 进程管理
   - 设备驱动管理
   - VFS虚拟文件系统



文件描述符存储在文件描述符表（数组，进程可以打开多个文件），而文件描述符表在进程的PCB进程控制块当中，PCB进程控制块保存在内核当中。



文件描述符表大小为1024，即默认可以打开的文件数量为1024个。文件描述符表的前三个位置被标准输入`STDIN_FILENO`、标准输出`STDOUT_FILENO`、标准错误`STDERR_FILENO`占用，这三个文件默认是打开的状态，这三个文件描述符都指向了当前终端（设备文件，对应Linux的一切皆文件）。



即一个文件可以被打开多次，但对应的文件描述符是不一样的。



打开的时候找最小的空闲的文件描述符，删除的时候会被释放。



### I/O函数

#### open函数

下面介绍`open`函数

```c
 #include <sys/types.h> //flags定义的宏
 #include <sys/stat.h> //flags定义的宏
 #include <fcntl.h> //函数声明
		//打开一个已经存在的文件
       int open(const char *pathname, int flags);
		  
		//创建一个新的文件
       int open(const char *pathname, int flags, mode_t mode);
```

```c
/*
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>

    // 打开一个已经存在的文件
    int open(const char *pathname, int flags);
        参数：
            - pathname：要打开的文件路径
            - flags：对文件的操作权限设置还有其他的设置
              O_RDONLY,  O_WRONLY,  O_RDWR  这三个设置是互斥的
        返回值：返回一个新的文件描述符，如果调用失败，返回-1

    errno：属于Linux系统函数库，库里面的一个全局变量，记录的是最近的错误号。

    #include <stdio.h>
    void perror(const char *s);作用：打印errno对应的错误描述
        s参数：用户描述，比如hello,最终输出的内容是  hello:xxx(实际的错误描述)
    

    // 创建一个新的文件
    int open(const char *pathname, int flags, mode_t mode);
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {

    // 打开一个文件
    int fd = open("a.txt", O_RDONLY);

    if(fd == -1) {
        perror("open");
    }
    // 读写操作

    // 关闭
    close(fd);

    return 0;
}
```

```c
/*
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>

    int open(const char *pathname, int flags, mode_t mode);
        参数：
            - pathname：要创建的文件的路径
            - flags：对文件的操作权限和其他的设置
                - 必选项：O_RDONLY,  O_WRONLY, O_RDWR  这三个之间是互斥的
                - 可选项：O_CREAT 文件不存在，创建新文件
            - mode：八进制的数，表示创建出的新的文件的操作权限，比如：0775
            最终的权限是：mode & ~umask
            0777   ->   111111111
        &   0775   ->   111111101
        ----------------------------
                        111111101
        按位与：0和任何数都为0
        umask的作用就是抹去某些权限。

        flags参数是一个int类型的数据，占4个字节，32位。
        flags 32个位，每一位就是一个标志位。

*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {

    // 创建一个新的文件
    int fd = open("create.txt", O_RDWR | O_CREAT, 0777); //使用或添加权限

    if(fd == -1) {
        perror("open");
    }

    // 关闭
    close(fd);

    return 0;
}
```

#### write/read函数

```c
/*  
    #include <unistd.h>
    ssize_t read(int fd, void *buf, size_t count);
        参数：
            - fd：文件描述符，open得到的，通过这个文件描述符操作某个文件
            - buf：需要读取数据存放的地方，数组的地址（传出参数）
            - count：指定的数组的大小
        返回值：
            - 成功：
                >0: 返回实际的读取到的字节数
                =0：文件已经读取完了
            - 失败：-1 ，并且设置errno

    #include <unistd.h>
    ssize_t write(int fd, const void *buf, size_t count);
        参数：
            - fd：文件描述符，open得到的，通过这个文件描述符操作某个文件
            - buf：要往磁盘写入的数据，数据
            - count：要写的数据的实际的大小
        返回值：
            成功：实际写入的字节数
            失败：返回-1，并设置errno
*/
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {

    // 1.通过open打开english.txt文件
    int srcfd = open("english.txt", O_RDONLY);
    if(srcfd == -1) {
        perror("open");
        return -1;
    }

    // 2.创建一个新的文件（拷贝文件）
    int destfd = open("cpy.txt", O_WRONLY | O_CREAT, 0664);
    if(destfd == -1) {
        perror("open");
        return -1;
    }

    // 3.频繁的读写操作
    char buf[1024] = {0};
    int len = 0;
    while((len = read(srcfd, buf, sizeof(buf))) > 0) {
        write(destfd, buf, len);
    }

    // 4.关闭文件
    close(destfd);
    close(srcfd);


    return 0;
}

```

lseek函数

```c
/*  
    标准C库的函数
    #include <stdio.h>
    int fseek(FILE *stream, long offset, int whence);

    Linux系统函数
    #include <sys/types.h>
    #include <unistd.h>
    off_t lseek(int fd, off_t offset, int whence);
        参数：
            - fd：文件描述符，通过open得到的，通过这个fd操作某个文件
            - offset：偏移量
            - whence:
                SEEK_SET
                    设置文件指针的偏移量
                SEEK_CUR
                    设置偏移量：当前位置 + 第二个参数offset的值
                SEEK_END
                    设置偏移量：文件大小 + 第二个参数offset的值
        返回值：返回文件指针的位置


    作用：
        1.移动文件指针到文件头
        lseek(fd, 0, SEEK_SET);

        2.获取当前文件指针的位置
        lseek(fd, 0, SEEK_CUR);

        3.获取文件长度
        lseek(fd, 0, SEEK_END);

        4.拓展文件的长度，当前文件10b, 110b, 增加了100个字节
        lseek(fd, 100, SEEK_END)
        注意：需要写一次数据

*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {

    int fd = open("hello.txt", O_RDWR);

    if(fd == -1) {
        perror("open");
        return -1;
    }

    // 扩展文件的长度
    int ret = lseek(fd, 100, SEEK_END);
    if(ret == -1) {
        perror("lseek");
        return -1;
    }

    // 写入一个空数据
    write(fd, " ", 1);

    // 关闭文件
    close(fd);

    return 0;
}
```

#### stat、Istat函数

```c
/*
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <unistd.h>

    int stat(const char *pathname, struct stat *statbuf);
        作用：获取一个文件相关的一些信息
        参数:
            - pathname：操作的文件的路径
            - statbuf：结构体变量，传出参数，用于保存获取到的文件的信息
        返回值：
            成功：返回0
            失败：返回-1 设置errno

    int lstat(const char *pathname, struct stat *statbuf);
        参数:
            - pathname：操作的文件的路径
            - statbuf：结构体变量，传出参数，用于保存获取到的文件的信息
        返回值：
            成功：返回0
            失败：返回-1 设置errno

*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main() {

    struct stat statbuf;

    int ret = stat("a.txt", &statbuf);

    if(ret == -1) {
        perror("stat");
        return -1;
    }

    printf("size: %ld\n", statbuf.st_size);


    return 0;
}/*
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <unistd.h>

    int stat(const char *pathname, struct stat *statbuf);
        作用：获取一个文件相关的一些信息（假如是软链接文件则返回原文件的的信息）
        参数:
            - pathname：操作的文件的路径
            - statbuf：结构体变量，传出参数，用于保存获取到的文件的信息
        返回值：
            成功：返回0
            失败：返回-1 设置errno

    int lstat(const char *pathname, struct stat *statbuf);
    	作用：获取一个软连接文件相关的一些信息
        参数:
            - pathname：操作的文件的路径
            - statbuf：结构体变量，传出参数，用于保存获取到的文件的信息
        返回值：
            成功：返回0
            失败：返回-1 设置errno

*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main() {

    struct stat statbuf;

    int ret = stat("a.txt", &statbuf);

    if(ret == -1) {
        perror("stat");
        return -1;
    }

    printf("size: %ld\n", statbuf.st_size);


    return 0;
}
```

```c
struct stat  
{   
    dev_t       st_dev;     /* ID of device containing file -文件所在设备的ID*/  
    ino_t       st_ino;     /* inode number -inode节点号*/    
    mode_t      st_mode;    /* protection -文件的类型喝存取权限*/    
    nlink_t     st_nlink;   /* number of hard links -链向此文件的连接数(硬连接)*/    
    uid_t       st_uid;     /* user ID of owner -user id*/    
    gid_t       st_gid;     /* group ID of owner - group id*/    
    dev_t       st_rdev;    /* device ID (if special file) -设备号，针对设备文件*/    
    off_t       st_size;    /* total size, in bytes -文件大小，字节为单位*/    
    blksize_t   st_blksize; /* blocksize for filesystem I/O -块的大小*/    
    blkcnt_t    st_blocks;  /* number of blocks allocated -文件所占块数*/    
    time_t      st_atime;   /* time of last access -最近存取时间*/    
    time_t      st_mtime;   /* time of last modification -最近修改时间*/    
    time_t      st_ctime;   /* time of last status change - */    
};  
```

其中`mode_t`为16位，其中每一位代表一个标识位。



![image-20240315151022688](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240315151022688.png)



故此，当判断是否有对应权限的时候，应该使用`&`操作，而且判断文件类型则使用`(st_mode & S_IFMT) == 文件类型`，其中文件类型如上图所示共七种，最终得到的结果喝宏进行对比。



#### stat来实现ls -s

```c
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>

// 模拟实现ls -l指令
// 传递至少一个参数，即可执行程序的路径（名称），其余的在命令行中输入参数会放入数组
int main(int argc, char *argv[])
{
    // 判断输入的参数是否正确，给出提示
    if (argc < 2)
    {
        printf("%s filename\n", argv[0]);
        exit(); // return -1;
    }

    // 通过stat函数获取用户输入的文件的信息
    struct stat st;
    int ret = stat(argv[1], &st);
    if (ret == -1)
    {
        perror("stat");
        return -1; // exit();
    }

    // 获取文件类型和文件权限
    char perms[11] = {0}; // 最后一位留给空字符，用于保存文件类型和文件权限
    switch (st.st_mode & __S_IFMT)
    {
    case __S_IFLNK:
        perms[0] = 'l';
        break;
    case __S_IFDIR:
        perms[0] = 'd';
        break;
    case __S_IFREG:
        perms[0] = '-';
        break;
    case __S_IFBLK:
        perms[0] = 'b';
        break;
    case __S_IFCHR:
        perms[0] = 'c';
        break;
    case __S_IFSOCK:
        perms[0] = 's';
        break;
    case __S_IFIFO:
        perms[0] = 'p';
        break;
    default:
        perms[0] = '?';
        break;
    }

    // 文件所有者
    perms[1] = (st.st_mode & S_IRUSR) ? 'r' : '-';
    perms[2] = (st.st_mode & S_IWUSR) ? 'w' : '-';
    perms[3] = (st.st_mode & S_IXUSR) ? 'x' : '-';

    // 文件所在组
    perms[4] = (st.st_mode & S_IRGRP) ? 'r' : '-';
    perms[5] = (st.st_mode & S_IWGRP) ? 'w' : '-';
    perms[6] = (st.st_mode & S_IXGRP) ? 'x' : '-';

    // 其他人
    perms[7] = (st.st_mode & S_IROTH) ? 'r' : '-';
    perms[8] = (st.st_mode & S_IWOTH) ? 'w' : '-';
    perms[9] = (st.st_mode & S_IXOTH) ? 'x' : '-';

    // 硬连接数
    int linkNum = st.st_nlink;

    // 文件所有者
    char *fileUser = getpwuid(st.st_uid)->pw_name; // getpwuid返回一个指向结构体passwd的指针，passwd里面有char *pw_name指针

    // 文件所在组
    char *fileGrp = getgrgid(st.st_gid)->gr_name;

    // 文件大小
    long int fileSize = st.st_size;

    // 获取修改的时间
    char *time = ctime(&st.st_mtime);//转换时间函数，参数为地址

    char mtime[512] = {0};
    strncpy(mtime, time, strlen(time) - 1);

    char buf[1024];//定义数组
    sprintf(buf, "%s %d %s %s %ld %s %s", perms, linkNum, fileUser, fileGrp, fileSize, mtime, argv[1]);//添加内容

    printf("%s\n", buf);
    return 0;
}
```

### 文件属性操作函数

#### access函数

```c
/*
    #include <unistd.h>
    int access(const char *pathname, int mode);
        作用：判断某个文件是否有某个权限，或者判断文件是否存在
        参数：
            - pathname: 判断的文件路径
            - mode:
                R_OK: 判断是否有读权限
                W_OK: 判断是否有写权限
                X_OK: 判断是否有执行权限
                F_OK: 判断文件是否存在
        返回值：成功返回0， 失败返回-1
*/

#include <unistd.h>
#include <stdio.h>

int main() {

    int ret = access("a.txt", F_OK);
    if(ret == -1) {
        perror("access");
    }

    printf("文件存在！！!\n");

    return 0;
}
```

#### chmode函数

```c
/*
    #include <sys/stat.h>
    int chmod(const char *pathname, mode_t mode);
        修改文件的权限
        参数：
            - pathname: 需要修改的文件的路径
            - mode:需要修改的权限值，八进制的数/宏值
        返回值：成功返回0，失败返回-1

*/
#include <sys/stat.h>
#include <stdio.h>
int main() {

    int ret = chmod("a.txt", 0777);

    if(ret == -1) {
        perror("chmod");
        return -1;
    }

    return 0;
}
```

#### truncate函数

```c
/*
    #include <unistd.h>
    #include <sys/types.h>
    int truncate(const char *path, off_t length);
        作用：缩减或者扩展文件的尺寸至指定的大小
        参数：
            - path: 需要修改的文件的路径
            - length: 需要最终文件变成的大小
        返回值：
            成功返回0， 失败返回-1
*/

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main() {

    int ret = truncate("b.txt", 5);

    if(ret == -1) {
        perror("truncate");
        return -1;
    }

    return 0;
}
```

### 目录操作函数

#### mkdir函数

```c
/*
    #include <sys/stat.h>
    #include <sys/types.h>
    int mkdir(const char *pathname, mode_t mode);
        作用：创建一个目录
        参数：
            pathname: 创建的目录的路径
            mode: 权限，八进制的数
        返回值：
            成功返回0， 失败返回-1
*/

#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>

int main() {

    int ret = mkdir("aaa", 0777);

    if(ret == -1) {
        perror("mkdir");
        return -1;
    }

    return 0;
}
```

#### rmdir函数

#### rename函数

```c
/*
    #include <stdio.h>
    int rename(const char *oldpath, const char *newpath);

*/
#include <stdio.h>

int main() {

    int ret = rename("aaa", "bbb");

    if(ret == -1) {
        perror("rename");
        return -1;
    }

    return 0;
}
```

#### chdir/getcwd函数

```c
/*

    #include <unistd.h>
    int chdir(const char *path);
        作用：修改进程的工作目录
            比如在/home/nowcoder 启动了一个可执行程序a.out, 进程的工作目录 /home/nowcoder
        参数：
            path : 需要修改的工作目录
        返回值：
            成功返回0， 失败返回-1

    #include <unistd.h>
    char *getcwd(char *buf, size_t size);
        作用：获取当前工作目录
        参数：
            - buf : 存储的路径，指向的是一个数组（传出参数）
            - size: 数组的大小
        返回值：
            返回的指向的一块内存，这个数据就是第一个参数

*/
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main() {

    // 获取当前的工作目录
    char buf[128];
    getcwd(buf, sizeof(buf));
    printf("当前的工作目录是：%s\n", buf);

    // 修改工作目录
    int ret = chdir("/home/nowcoder/Linux/lesson13");
    if(ret == -1) {
        perror("chdir");
        return -1;
    } 

    // 创建一个新的文件
    int fd = open("chdir.txt", O_CREAT | O_RDWR, 0664);
    if(fd == -1) {
        perror("open");
        return -1;
    }

    close(fd);

    // 获取当前的工作目录
    char buf1[128];
    getcwd(buf1, sizeof(buf1));
    printf("当前的工作目录是：%s\n", buf1);
    
    return 0;
}
```

### 目录遍历函数

#### opendir函数

```c
    #include <sys/types.h>
    #include <dirent.h>
    DIR *opendir(const char *name);
/*        参数：
            - name: 需要打开的目录的名称
        返回值：
            DIR * 类型，理解为目录流
            错误返回NULL  */
```

#### readdir函数

```c
 // 读取目录中的数据
    #include <dirent.h>
    struct dirent *readdir(DIR *dirp);
/*        - 参数：dirp是opendir返回的结果
        - 返回值：
            struct dirent，代表读取到的文件的信息，调用一次往后一次
            读取到了末尾或者失败了，返回NULL */
```

#### closedir函数

```c
    // 关闭目录
    #include <sys/types.h>
    #include <dirent.h>
    int closedir(DIR *dirp);
```

#### 计算普通文件数量

```c
/*
    // 打开一个目录
    #include <sys/types.h>
    #include <dirent.h>
    DIR *opendir(const char *name);
        参数：
            - name: 需要打开的目录的名称
        返回值：
            DIR * 类型，理解为目录流
            错误返回NULL


    // 读取目录中的数据
    #include <dirent.h>
    struct dirent *readdir(DIR *dirp);
        - 参数：dirp是opendir返回的结果
        - 返回值：
            struct dirent，代表读取到的文件的信息，调用一次往后一次
            读取到了末尾或者失败了，返回NULL

    // 关闭目录
    #include <sys/types.h>
    #include <dirent.h>
    int closedir(DIR *dirp);

*/
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int getFileNum(const char * path);

// 读取某个目录下所有的普通文件的个数
int main(int argc, char * argv[]) {

    if(argc < 2) {
        printf("%s path\n", argv[0]);
        return -1;
    }

    int num = getFileNum(argv[1]);

    printf("普通文件的个数为：%d\n", num);

    return 0;
}

// 用于获取目录下所有普通文件的个数
int getFileNum(const char * path) {

    // 1.打开目录
    DIR * dir = opendir(path);

    if(dir == NULL) {
        perror("opendir");
        exit(0);
    }

    struct dirent *ptr;

    // 记录普通文件的个数
    int total = 0;

    while((ptr = readdir(dir)) != NULL) {

        // 获取名称
        char * dname = ptr->d_name;

        // 忽略掉. 和.. 即当前目录和上级目录
        if(strcmp(dname, ".") == 0 || strcmp(dname, "..") == 0) {
            continue;
        }

        // 判断是否是普通文件还是目录
        if(ptr->d_type == DT_DIR) {
            // 目录,需要继续读取这个目录
            char newpath[256];
            sprintf(newpath, "%s/%s", path, dname);
            total += getFileNum(newpath);
        }

        if(ptr->d_type == DT_REG) {
            // 普通文件
            total++;
        }


    }

    // 关闭目录
    closedir(dir);

    return total;
}
```

```c
struct dirent
{
   long d_ino; /* inode number 索引节点号 */
   off_t d_off; /* offset to this dirent 在目录文件中的偏移 */
   unsigned short d_reclen; /* length of this d_name 文件名长 */
   unsigned char d_type; /* the type of d_name 文件类型 */
   char d_name [NAME_MAX+1]; /* file name (null-terminated) 文件名，最长255字符 */
}
```

### 文件描述符函数

#### dup函数

```c
/*
    #include <unistd.h>
    int dup(int oldfd);
        作用：复制一个新的文件描述符
        fd=3, int fd1 = dup(fd),
        fd指向的是a.txt, fd1也是指向a.txt
        从空闲的文件描述符表中找一个最小的，作为新的拷贝的文件描述符


*/

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main() {

    int fd = open("a.txt", O_RDWR | O_CREAT, 0664);

    int fd1 = dup(fd);

    if(fd1 == -1) {
        perror("dup");
        return -1;
    }

    printf("fd : %d , fd1 : %d\n", fd, fd1);

    close(fd);

    char * str = "hello,world";
    int ret = write(fd1, str, strlen(str));
    if(ret == -1) {
        perror("write");
        return -1;
    }

    close(fd1);

    return 0;
}
```

#### dup2函数

```c
/*
    #include <unistd.h>
    int dup2(int oldfd, int newfd);
        作用：重定向文件描述符
        oldfd 指向 a.txt, newfd 指向 b.txt
        调用函数成功后：newfd 和 b.txt 做close, newfd 指向了 a.txt
        oldfd 必须是一个有效的文件描述符
        oldfd和newfd值相同，相当于什么都没有做
*/
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main() {

    int fd = open("1.txt", O_RDWR | O_CREAT, 0664);
    if(fd == -1) {
        perror("open");
        return -1;
    }

    int fd1 = open("2.txt", O_RDWR | O_CREAT, 0664);
    if(fd1 == -1) {
        perror("open");
        return -1;
    }

    printf("fd : %d, fd1 : %d\n", fd, fd1);

    int fd2 = dup2(fd, fd1);
    if(fd2 == -1) {
        perror("dup2");
        return -1;
    }

    // 通过fd1去写数据，实际操作的是1.txt，而不是2.txt
    char * str = "hello, dup2";
    int len = write(fd1, str, strlen(str));

    if(len == -1) {
        perror("write");
        return -1;
    }

    printf("fd : %d, fd1 : %d, fd2 : %d\n", fd, fd1, fd2);

    close(fd);
    close(fd1);

    return 0;
}
```

### 文件描述符/权限操作函数

#### fcntl函数

只掌握复制文件描述符和对文件权限进行处理。

```c
/*

    #include <unistd.h>
    #include <fcntl.h>

    int fcntl(int fd, int cmd, ...);//可变参数
    参数：
        fd : 表示需要操作的文件描述符
        cmd: 表示对文件描述符进行如何操作
            - F_DUPFD : 复制文件描述符,复制的是第一个参数fd，得到一个新的文件描述符（返回值）
                int ret = fcntl(fd, F_DUPFD);

            - F_GETFL : 获取指定的文件描述符文件状态flag
              获取的flag和我们通过open函数传递的flag是一个东西。

            - F_SETFL : 设置文件描述符文件状态flag
              必选项：O_RDONLY, O_WRONLY, O_RDWR 不可以被修改
              可选性：O_APPEND, O)NONBLOCK
                O_APPEND 表示追加数据
                NONBLOK 设置成非阻塞
        
        阻塞和非阻塞：描述的是函数调用的行为。
*/

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int main() {

    // 1.复制文件描述符
    // int fd = open("1.txt", O_RDONLY);
    // int ret = fcntl(fd, F_DUPFD);

    // 2.修改或者获取文件状态flag
    int fd = open("1.txt", O_RDWR);
    if(fd == -1) {
        perror("open");
        return -1;
    }

    // 获取文件描述符状态flag
    int flag = fcntl(fd, F_GETFL);
    if(flag == -1) {
        perror("fcntl");
        return -1;
    }
    flag |= O_APPEND;   // flag = flag | O_APPEND

    // 修改文件描述符状态的flag，给flag加入O_APPEND这个标记
    int ret = fcntl(fd, F_SETFL, flag);
    if(ret == -1) {
        perror("fcntl");
        return -1;
    }

    char * str = "nihao";
    write(fd, str, strlen(str));

    close(fd);

    return 0;
}
```

# Linux多进程开发

## 程序和进程

程序是包含一系列信息的文件，这些信息描述了如何在运行时创建一个进程：

1. 二进制格式标识：每个程序文件都包含用于描述可执行文件格式的元信息。内核利用此信息来解
   释文件中的其他信息。(ELF可执行连接格式)
2. 机器语言指令：对程序算法进行编码。
3. 程序入口地址：标识程序开始执行时的起始指令位置。
4. 数据︰程序文件包含的变量初始值和程序使用的字面量值（比如字符串)。
5. 符号表及重定位表︰描述程序中函数和变量的位置及名称。这些表格有多重用途，其中包括调试和运行时的符号解析（动态链接）。
6. 共享库和动态链接信息：程序文件所包含的一些字段，列出了程序运行时需要使用的共享库，以及加载共享库的动态连接器的路径名。
7. 其他信息：程序文件还包含许多其他信息，用以描述如何创建进程。



进程是正在运行的程序的实例。是一个具有一定独立功能的程序关于某个数据集合的一次运行活动。它是操作系统动态执行的基本单元，在传统的操作系统中，进程既是基本的分配单元，也是基本的执行单元。



可以用一个程序来创建多个进程，进程是由内核定义的抽象实体，并为该实体分配用以执行程序的各项系统资源。从内核的角度看，进程由用户内存空间和一系列内核数据结构组成。其中用户内存空间包含了程序代码及代码所使用的变量，而内核数据结构则用于维护进程状态信息。记录在内核数据结构中的信息包括许多与进程相关的标识号(IDs)、虚拟内存表、打开文件的描述符表、信号传递及处理的有关信息、进程资源使用及限制、当前工作目录和大量的其他信息。



每个进程都由进程号来标识，其类型为pid_t(整型)，进程号的范围:0~32767。进程号总是唯一的，但可以重用。当一个进程终止后，其进程号就可以再次使用。



任何进程（除init进程）都是由另一个进程创建，该进程称为被创建进程的父进程，对应的进程号称为父进程号(PPID)，一般父进程是当前终端。



进程组是一个或多个进程的集合。他们之间相互关联，进程组可以接收同一终端的各种信号，关联的进程有一个进程组号(PGID)。默认情况下，当前的进程号会当做当前的进程组号。

## 单道和多道程序设计



单道程序，即在计算机内存中只允许一个的程序运行。



多道程序设计技术是在计算机内存中同时存放几道相互独立的程序，使它们在管理程序控制下，相互穿插运行，两个或两个以上程序在计算机系统中同处于开始到结束之间的状态，这些程序共享计算机系统资源。引入多道程序设计技术的根本目的是为了提高cPU的利用率。



对于一个单CPU系统来说，程序同时处于运行状态只是一种宏观上的概念．他们虽然都已经开始运行，但就微观而言，任意时刻，CPU上运行的程序只有一个。在多道程序设计模型中，多个进程轮流使用CPU。而当下常见CPU为纳秒级，1秒可以执行大约10 亿条指令。由于人眼的反应速度是毫秒级，所以看似同时在运行。

## 时间片

时间片 (timeslice)又称为"量子(quantum)“或"处理器片(processor slice)"是操作系统分配给每个正在运行的进程微观上的一段CPU时间。事实上，虽然一台计算机通常可能有多个CPU，但是同一个CPU永远不可能真正地同时运行多个任务。在只考虑一个CPU的情况下，这些进程"看起来像"同时运行的，实则是轮番穿插地运行,由于时间片通常很短(在 Linux 上为5ms - 800ms)，用户不会感觉到。



时间片由操作系统内核的调度程序分配给每个进程。首先，内核会给每个进程分配相等的初始时间片，然后每个进程轮番地执行相应的时间，当所有进程都处于时间片耗尽的状态时，内核会重新为每个进程计算并分配时间片，如此往复。

## 并发和并行

并行(parallel)：指在同一时刻，有多条指令在多个处理器上同时执行。
并发(concurrency)：指在同一时刻只能有一条指令执行，但多个进程指令被快速的轮换执行，使得在宏观上具有多个进程同时执行的效果，但在微观上并不是同时执行的，只是把时间分成若干段,使多个进程快速交替的执行。

## 进程控制块



为了管理进程，内核必须对每个进程所做的事情进行清楚的描述。内核为每个进程分配一个PCB(Processing Control Block)进程控制块，维护进程相关的信息，Linux内核的进程控制块是task_struct结构体。



在/usr/src/linux-headers-xxx/include/linux/sched.h文件中可以查看struct task_struct结构体定义。其内部成员有很多，我们只需要掌握以下部分即可:

1. 进程id：系统中每个进程有唯一的 id，用pid_t类型表示，其实就是一个非负整数
2. 进程的状态：有就绪、运行、挂起、停止等状态。
3. 进程切换时需要保存和恢复的一些CPU寄存器描述虚拟地址空间的信息
4. 描述控制终端的信息
5. 当前工作目录(Current working Directory)
6. umask掩码
7. 文件描述符表，包含很多指向file结构体的指针
8. 和信号相关的信息
9. 用户`id`和组`id`
10. 会话(Session)和进程组
11. 进程可以使用的资源上限(Resource Limit)

## 进程状态

进程状态反映进程执行过程的变化。这些状态随着进程的执行和外界条件的变化而转换。



1、进程状态相关命令：

- `ps aux/ajx`：a显示终端上的所有进程，包括其他用户的进程。u显示进程的详细信息。x显示没有控制终端的进程。j列出与作业控制相关的信息。下面介绍一些参数：

  - TTY参数意义：所处的终端

  - STAT参数意义：
    - `D`：不可中断Uninterruptible (usually IO)
    - `R`：正在运行，或在队列中的进程
    - `s`(大写)：处于休眠状态
    - `T`：停止或被追踪
    - `Z`：僵尸进程
    - `W`：进入内存交换（从内核2.6开始无效)
    - `x`：死掉的进程
    - `<`：高优先级
    - `N`：低优先级
    - `s`：包含子进程
    - `+`：位于前台的进程组

  - PPID参数意义：父进程的ID

  - PGID参数意义：进程组的ID

  - SID参数意义：会话的ID

- `top`：实时显示进程动。可以在使用top命令时加上`-d`来指定显示信息更新的时间间隔。在top命令执行后，可以按以下按键对显示的结果进行排序/杀死进程:

  - `M`：根据内存使用量排序

  - `P`：根据CPU占有率排序

  - `T`：根据进程运行时间长短排序

  - `U`：根据用户名来筛选进程

  - `K`：输入指定的 PID杀死进程，杀死自己终端需要加上参数`-9`

3、杀死进程相关命令：

- `kill [-signal] pid`
- `kill -l` ：列出所有信号
- `kill -SIGKILL`：进程ID
- `kill-9`：进程ID
- `killall name`：根据进程名杀死进程

4、进程号和进程组相关函数:

- `pid_t getpid (void);`
- `pid_t getppid (void);`
- `pid_t getpgid(pid_t pid);`

## 终端

在 UNIX 系统中，用户通过终端登录系统后得到一个 shell 进程，这个终端成为 shell 进程的控制终端（Controlling Terminal），进程中，控制终端是

保存在 PCB 中的信息，而 fork() 会复制 PCB 中的信息，因此由 shell 进程启动的其它进程的控制终端也是这个终端。



默认情况下（没有重定向），每个进程的标准输入、标准输出和标准错误输出都指向控制终端，进程从标准输入读也就是读用户的键盘输入，进程往标准输出或标准错误输出写也就是输出到显示器上。



在控制终端输入一些特殊的控制键可以给前台进程发信号，例如 Ctrl + C 会产生 SIGINT 信号，Ctrl + \ 会产生 SIGQUIT 信号。

## 进程组

进程组（shell作业）和会话在进程之间形成了一种两级层次关系：进程组是一组相关进程的集合，会话是一组相关进程组的集合。进程组和会话是为支持 shell 作业控制而定义的抽象概念，用户通过 shell 能够交互式地在前台或后台运行命令。



进行组由一个或多个共享同一进程组标识符（PGID）的进程组成。一个进程组拥有一个进程组首进程，该进程是创建该组的进程，其进程 ID 为该进程组的 ID，新进程会继承其父进程所属的进程组 ID。



进程组拥有一个生命周期，其开始时间为首进程创建组的时刻，结束时间为最后一个成员进程退出组的时刻。一个进程可能会因为终止而退出进程组，也可能会因为加入了另外一个进程组而退出进程组。进程组首进程无需是最后一个离开进程组的成员。



## 会话

会话是一组进程组的集合。会话首进程是创建该新会话的进程，其进程ID会成为会话ID。新进程会继承其父进程的会话 ID。一个会话中的所有进程共享单个控制终端（控制终端是指我可以通过比如按键产生一些信号，从而控制进程）。控制终端会在会话首进程首次打开一个终端设备时被建立。一个终端最多可能会成为一个会话的控制终端。



在任一时刻，会话中的其中一个进程组会成为终端的前台进程组，其他进程组会成为后台进程组。只有前台进程组中的进程才能从控制终端中读取输入。当用户在控制终端中输入终端字符生成信号后，该信号会被发送到前台进程组中的所有成员。



当控制终端的连接建立起来之后，会话首进程会成为该终端的控制进程。



![image-20240327075020120](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240327075020120.png)



进程组、会话操作函数:

1. pid_t getpgrp(void);
2. pid_t getpgid(pid_t pid);
3. int setpgid(pid_t pid, pid_t pgid);
4. pid_t getsid(pid_t pid);
5. pid_t setsid(void);

## 守护进程

守护进程（Daemon Process），也就是通常说的 Daemon 进程（精灵进程），是Linux 中的后台服务进程。它是一个生存期较长的进程，通常独立于控制终端并且周期性地执行某种任务或等待处理某些发生的事件。一般采用以 d 结尾的名字。



守护进程具备下列特征：

1. 生命周期很长，守护进程会在系统启动的时候被创建并一直运行直至系统被关闭。
2. 它在后台运行并且不拥有控制终端。没有控制终端确保了内核永远不会为守护进程自动生成任何控制信号以及终端相关的信号（如 SIGINT、SIGQUIT）。

Linux 的大多数服务器就是用守护进程实现的。比如，Internet 服务器 inetd，Web 服务器 httpd 等。



守护进程的创建服务步骤：

1. 执行一个 `fork()`，之后父进程退出，子进程继续执行。（创建会话，进程组长和会话长不能同一个，而且父进程结束后会产生`shell`结束符，因此退出，）
2.  子进程调用`setsid()` 开启一个新会话。(完成没有控制终端的要求 ，不会自动连接控制终端)
3. 清除进程的 `umask`（掩码） 以确保当守护进程创建文件和目录时拥有所需的权限。（非必须）
4. 修改进程的当前工作目录，通常会改为根目录（/）。（防止在别的地方进行启动时候，关闭该地方导致失效）（非必须）
5. 关闭守护进程从其父进程继承而来的所有打开着的文件描述符。（防止连接到控制终端）（非必须）
6. 在关闭了文件描述符0、1、2之后，守护进程通常会打开`/dev/null`并使用`dup2()` 使所有这些描述符指向这个设备。（非必须）

7. 核心业务逻辑

```c
/*
    写一个守护进程，每隔2s获取一下系统时间，将这个时间写入到磁盘文件中。
*/

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <signal.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void work(int num) {
    // 捕捉到信号之后，获取系统时间，写入磁盘文件
    time_t tm = time(NULL);
    struct tm * loc = localtime(&tm);
    // char buf[1024];

    // sprintf(buf, "%d-%d-%d %d:%d:%d\n",loc->tm_year,loc->tm_mon
    // ,loc->tm_mday, loc->tm_hour, loc->tm_min, loc->tm_sec);

    // printf("%s\n", buf);

    char * str = asctime(loc);
    int fd = open("time.txt", O_RDWR | O_CREAT | O_APPEND, 0664);
    write(fd ,str, strlen(str));
    close(fd);
}

int main() {

    // 1.创建子进程，退出父进程
    pid_t pid = fork();

    if(pid > 0) {
        exit(0);
    }

    // 2.将子进程重新创建一个会话
    setsid();

    // 3.设置掩码
    umask(022);

    // 4.更改工作目录
    chdir("/home/nowcoder/");

    // 5. 关闭、重定向文件描述符
    int fd = open("/dev/null", O_RDWR);
    dup2(fd, STDIN_FILENO);
    dup2(fd, STDOUT_FILENO);
    dup2(fd, STDERR_FILENO);

    // 6.业务逻辑

    // 捕捉定时信号
    struct sigaction act;
    act.sa_flags = 0;
    act.sa_handler = work;
    sigemptyset(&act.sa_mask);
    sigaction(SIGALRM, &act, NULL);

    struct itimerval val;
    val.it_value.tv_sec = 2;
    val.it_value.tv_usec = 0;
    val.it_interval.tv_sec = 2;
    val.it_interval.tv_usec = 0;

    // 创建定时器
    setitimer(ITIMER_REAL, &val, NULL);

    // 不让进程结束
    while(1) {
        sleep(10);
    }

    return 0;
}
```

## 进程控制

### 创建进程

系统允许一个进程创建新进程、新进程即为子进程，子进程还可以创建新的子进程，形成进程树结构模型。

```c
#include <sys/types.h>
#include <unistd.h>

pid_t fork (void);//fork n.分叉
/*返回值:
成功:子进程中返回 0，父进程中返回子进程ID失败:返回-1
失败的两个主要原因:
1．当前系统的进程数已经达到了系统规定的上限，这时errno 的值被设置
为EAGAIN
2．系统内存不足，这时errno 的值被设置为ENOMEM*/
```

```c
/*
    #include <sys/types.h>
    #include <unistd.h>

    pid_t fork(void);
        函数的作用：用于创建子进程。
        返回值：
            fork()的返回值会返回两次。一次是在父进程中，一次是在子进程中。
            在父进程中返回创建的子进程的ID,
            在子进程中返回0
            如何区分父进程和子进程：通过fork的返回值。
            在父进程中返回-1，表示创建子进程失败，并且设置errno

        父子进程之间的关系：
        区别：
            1.fork()函数的返回值不同
                父进程中: >0 返回的子进程的ID
                子进程中: =0
            2.pcb中的一些数据
                当前的进程的id pid
                当前的进程的父进程的id ppid
                信号集

        共同点：
            某些状态下：子进程刚被创建出来，还没有执行任何的写数据的操作
                - 用户区的数据
                - 文件描述符表
        
        父子进程对变量是不是共享的？
            - 刚开始的时候，是一样的，共享的。如果修改了数据，不共享了。
            - 读时共享（子进程被创建，两个进程没有做任何的写的操作），写时拷贝。
        
*/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {

    int num = 10;

    // 创建子进程
    pid_t pid = fork();

    // 判断是父进程还是子进程
    if(pid > 0) {
        // printf("pid : %d\n", pid);
        // 如果大于0，返回的是创建的子进程的进程号，当前是父进程
        printf("i am parent process, pid : %d, ppid : %d\n", getpid(), getppid());

        printf("parent num : %d\n", num);
        num += 10; //初始值相等但是后面操作不相关
        printf("parent num += 10 : %d\n", num);


    } else if(pid == 0) {
        // 当前是子进程
        printf("i am child process, pid : %d, ppid : %d\n", getpid(),getppid());
       
        printf("child num : %d\n", num);
        num += 100;
        printf("child num += 100 : %d\n", num);
    }

    // for循环，展示执行顺序的异步性
    for(int i = 0; i < 3; i++) {
        printf("i : %d , pid : %d\n", i , getpid());
        sleep(1);
    }

    return 0;
}

/*
实际上，更准确来说，Linux 的 fork() 使用是通过写时拷贝 (copy-on-write) 实现。
写时拷贝是一种可以推迟甚至避免拷贝数据的技术。
内核此时并不复制整个进程的地址空间，而是让父子进程共享同一个地址空间。
只用在需要写入的时候才会复制地址空间，从而使各个进行拥有各自的地址空间。
也就是说，资源的复制是在需要写入的时候才会进行，在此之前，只有以只读方式共享。
注意：fork之后父子进程共享文件，
fork产生的子进程与父进程相同的文件文件描述符指向相同的文件表，引用计数增加，共享文件偏移指针。
*/
```

### `gdb`多进程调试

使用GDB 调试的时候，GDB默认只能跟踪一个进程，可以在`fork`函数调用之前，通过指令设置GDB调试工具跟踪父进程或者是跟踪子进程，默认跟踪父进程。



1. 设置调试父进程或者子进程: `set follow-fork-mode`，默认是父进程
2. 设置调试模式: `set detach-on-fork on/off`，默认为on，表示调试当前进程的时候，其它的进程继续运行，如果为off，调试当前进程的时候．其它进程被GDB 挂起。
3. 查看调试的进程: `info inferiors`
4. 切换当前调试的进程: `inferior id`
5. 使进程脱离GDB 调试: `detach inferiors id`

```c
#include <stdio.h>
#include <unistd.h>

int main() {

    printf("begin\n");

    if(fork() > 0) {

        printf("我是父进程：pid = %d, ppid = %d\n", getpid(), getppid());

        int i;
        for(i = 0; i < 10; i++) {
            printf("i = %d\n", i);
            sleep(1);
        }

    } else {

        printf("我是子进程：pid = %d, ppid = %d\n", getpid(), getppid());
        
        int j;
        for(j = 0; j < 10; j++) {
            printf("j = %d\n", j);
            sleep(1);
        }

    }

    return 0;
}
```

### `exec`函数族

`exec`函数族的作用是根据指定的文件名找到可执行文件，并用它来取代调用进程的内容。换句话说，就是在调用进程内部执行一个可执行文件。



`exec`函数族的函数执行成功后不会返回，因为调用进程的实体，包括代码段．数据段和堆栈等都已经被新的内容取代，只留下进程ID等一些表面上的信息仍保持原样，颇有些神似"三十六计"中的"金蝉脱壳”。看上去还是旧的躯壳，却已经注入了新的灵魂。只有调用失败了，它们才会返回 -1，从原程序的调用点接着往下执行。



因为在调用`exec`函数后，虚拟内存中除了内核区外，用户区全部被调用`exec`函数的文件的用户区替换。大多数情况下，主进程还需要执行其他功能，所以一般需要生产子进程后在子进程中中调用`exec`函数。



```c
#include <unistd.h>
extern char **environ;

int execl(const char *path, const char *arg, ...); //常用，自编译可执行代码
int execlp(const char *file, const char *arg, ...); //常用，环境变量
int execle(const char *path, const char *arg,..., char * const envp[]);
int execv(const char *path, char *const argv[]);
int execvp(const char *file, char *const argv[]);
int execvpe(const char *file, char *const argv[],char *const envp[]);
```

1. `l`：调用程序每个命令行参数需单独写成列表形式并以空指针结束
2. `p`：如果函数参数 file 含 / 就视为路径名，否则按 PATH 环境变量指定的目录搜索可执行文件
3. `v`：需先构造一个命令行参数的指针数组，然后将数组地址作为调用程序参数
4. `e`：需先构造环境字符串指针数组，然后将数组地址传给函数使用新的环境变量代替调用进程的环境变量参数
5. `path`：可执行文件的路径名字
6. `file` ：按 PATH 环境变量指定的目录搜索可执行文件
7. `arg` ：可执行程序所带的命令行参数，第一个参数为可执行文件的名字（没什么用，一般写这个），从第二个参数开始就是程序所需参数列表，最后必须以NULL结束
8. `argv[]` ：命令行参数的指针数组
9. `envp[]` ：环境字符串指针数组

```c
/*  
    #include <unistd.h>
    int execl(const char *path, const char *arg, ...);
        - 参数：
            - path:需要指定的执行的文件的路径或者名称
                a.out /home/nowcoder/a.out 推荐使用绝对路径
                ./a.out hello world

            - arg:是执行可执行文件所需要的参数列表
                第一个参数一般没有什么作用，为了方便，一般写的是执行的程序的名称
                从第二个参数开始往后，就是程序执行所需要的的参数列表。
                参数最后需要以NULL结束（哨兵）

        - 返回值：
            只有当调用失败，才会有返回值，返回-1，并且设置errno
            如果调用成功，没有返回值。

*/
#include <unistd.h>
#include <stdio.h>

int main() {


    // 创建一个子进程，在子进程中执行exec函数族中的函数
    pid_t pid = fork();

    if(pid > 0) {
        // 父进程
        printf("i am parent process, pid : %d\n",getpid());
        sleep(1);//防止孤儿进程的产生
    
    }else if(pid == 0) {
        // 子进程
        // execl("hello","hello",NULL);只会输出hello world，子进程的其他代码不会执行，完全替代进入子进程

        execl("/bin/ps", "ps", "aux", NULL);//执行操作系统的shell命令
        perror("execl");
        printf("i am child process, pid : %d\n", getpid());

    }

    for(int i = 0; i < 3; i++) {
        printf("i = %d, pid = %d\n", i, getpid());
    }


    return 0;
}

```

```c
/*  
    #include <unistd.h>
    int execlp(const char *file, const char *arg, ... );
        - 会到环境变量中查找指定的可执行文件，如果找到了就执行，找不到就执行不成功。
        - 参数：
            - file:需要执行的可执行文件的文件名
                a.out
                ps

            - arg:是执行可执行文件所需要的参数列表
                第一个参数一般没有什么作用，为了方便，一般写的是执行的程序的名称
                从第二个参数开始往后，就是程序执行所需要的的参数列表。
                参数最后需要以NULL结束（哨兵）

        - 返回值：
            只有当调用失败，才会有返回值，返回-1，并且设置errno
            如果调用成功，没有返回值。


        int execv(const char *path, char *const argv[]);
        argv是需要的参数的一个字符串数组
        char * argv[] = {"ps", "aux", NULL};
        execv("/bin/ps", argv);

        int execve(const char *filename, char *const argv[], char *const envp[]);
        char * envp[] = {"/home/nowcoder", "/home/bbb", "/home/aaa"};


*/
#include <unistd.h>
#include <stdio.h>

int main() {


    // 创建一个子进程，在子进程中执行exec函数族中的函数
    pid_t pid = fork();

    if(pid > 0) {
        // 父进程
        printf("i am parent process, pid : %d\n",getpid());
        sleep(1);
    }else if(pid == 0) {
        // 子进程
        execlp("ps", "ps", "aux", NULL);
        printf("i am child process, pid : %d\n", getpid());

    }

    for(int i = 0; i < 3; i++) {
        printf("i = %d, pid = %d\n", i, getpid());
    }


    return 0;
}
```

### 结束进程

1. 标准C库IO函数：

   - 调用退出函数
   - 刷新IO缓存，关闭文件描述符
   - 调用_exit()系统调用
   - 进程终止运行

   ```c
   #include <stdlib.h>
   exit(int status);
   ```

2. Linux的IO函数（少用）：

   - 调用_exit()系统调用
   - 进程终止运行

   ```c
   #include <unistd.h>
   _exit(int status);
   ```

```c
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    printf("hello\n");//刷新缓冲区
    printf("world");

    _exit(0);//只显示hello，world放到缓冲区但没有刷新
   
    return 0;
}
```

### 孤儿进程

父进程运行结束，但子进程还在运行（未运行结束)，这样的子进程就称为孤儿进程(orphan Process) 。每当出现一个孤儿进程的时候，内核就把孤儿进程的父进程设置为 init , 而init进程会循环地 wait( )它的已经退出的子进程。因为本来是由父进程进行子进程的的交接，父进程没了，只能由init进程来进行接管。这样，当一个孤儿进程凄凉地结束了其生命周期的时候，init进程就会代表党和政府出面处理它的一切善后工作。因此孤儿进程并不会有什么危害。

​	

```c
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {

    int num = 10;

    // 创建子进程
    pid_t pid = fork();

    // 判断是父进程还是子进程
    if(pid > 0) {
        // printf("pid : %d\n", pid);
        // 如果大于0，返回的是创建的子进程的进程号，当前是父进程
        printf("i am parent process, pid : %d, ppid : %d\n", getpid(), getppid());


    } else if(pid == 0) {
        // 当前是子进程
        sleep(1); //设置睡一秒
        printf("i am child process, pid : %d, ppid : %d\n", getpid(),getppid());//
      
    }

    // for循环，展示执行顺序的异步性
    for(int i = 0; i < 3; i++) {
        printf("i : %d , pid : %d\n", i , getpid());
    }

    return 0;
}
```

此时子进程的父进程变成了1，被`init`接管了。

### 僵尸进程

每个进程结束之后，都会释放自己地址空间中的用户区数据，内核区的PCB没有办法自己释放掉，需要父进程去释放。进程终止时，父进程尚未回收资源，子进程残留资源（主要指PCB）存放于内核中，变成僵尸(Zombie)进程。



僵尸进程不能被`kill -9`杀死。



这样就会导致一个问题，如果父进程不调用`wait()`或`waitpid()`的话，那么保留的那段信息就不会释放，其进程号就会一直被占用，但是系统所能使用的进程号是有限的，如果大量的产生僵尸进程，将因为没有可用的进程号而导致系统不能产生新的进程，此即为僵尸进程的危害，应当避免。

```c
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {

    int num = 10;

    // 创建子进程
    pid_t pid = fork();

    // 判断是父进程还是子进程
    if(pid > 0) {
        // printf("pid : %d\n", pid);
        // 如果大于0，返回的是创建的子进程的进程号，当前是父进程
        while(1){
        printf("i am parent process, pid : %d, ppid : %d\n", getpid(), getppid());
        sleep(1);
        }


    } else if(pid == 0) {
        // 当前是子进程
        sleep(1); //设置睡一秒
        printf("i am child process, pid : %d, ppid : %d\n", getpid(),getppid());//
      
    }

    // for循环，展示执行顺序的异步性
    for(int i = 0; i < 3; i++) {
        printf("i : %d , pid : %d\n", i , getpid());
    }

    return 0;
}
```

此时父进程一直执行无法进行回收，子进程则变成僵尸进程

### 进程回收

在每个进程退出的时候，内核释放该进程所有的资源、包括打开的文件、占用的内存等。但是仍然为其保留一定的信息，这些信息主要主要指进程控制块PCB的信息(包括进程号、退出状态、运行时间等)。



父进程可以通过调用wait或waitpid得到它的退出状态同时彻底清除掉这个进程。



`wait ()`和`waitpid()`函数的功能一样，区别在于， `wait ()`函数会阻塞，`waitpid()`可以设置不阻塞，waitpid ()还可以指定等待哪个子进程结束。



注意：一次`wait`或`waitpid`调用只能清理一个子进程，清理多个子进程应使用循环。



退出信息相关宏函数：



退出

- `WIFEXITED(status)`：非0，进程正常退出
- `WEXITSTATUS (status)`：如果上面宏为真，获取进程退出的状态（ `exit()` 的参数）

终止

- `WIFSIGNALED(status)`：非0，进程异常终止
- `WTERMSIG(status)`：如果上面宏为真，获取使进程终止的信号编号

暂停

- `FSTOPPED (status)`：非0，进程处于暂停状态
- `WSTOPSIG(status)`：如果上面宏为真，获取使进程暂停的信号的编号
- `WIFCONTINUED (status)`：非0，进程暂停后已经继续运行



```c
/*
    #include <sys/types.h>
    #include <sys/wait.h>
    pid_t wait(int *wstatus);
        功能：等待任意一个子进程结束，如果任意一个子进程结束了，次函数会回收子进程的资源。
        参数：int *wstatus
            进程退出时的状态信息，传入的是一个int类型的地址，传出参数。
        返回值：
            - 成功：返回被回收的子进程的id
            - 失败：-1 (所有的子进程都结束，调用函数失败)

    调用wait函数的进程会被挂起（阻塞），直到它的一个子进程退出或者收到一个不能被忽略的信号时才被唤醒（相当于继续往下执行）
    如果没有子进程了，函数立刻返回，返回-1；如果子进程都已经结束了，也会立即返回，返回-1.

*/
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main() {

    // 有一个父进程，创建5个子进程（兄弟）
    pid_t pid;

    // 创建5个子进程
    for(int i = 0; i < 5; i++) {
        pid = fork();
        if(pid == 0) { //限制当是子进程的时候不允许它生产子进程
            break;
        }
    }

    if(pid > 0) {
        // 父进程
        while(1) {
            printf("parent, pid = %d\n", getpid());

            /* 	int ret = wait(NULL); 
            	printf("child die, pid = %d\n", ret); //此时被阻塞，直到一个子进程结束
            */
            int st;
            int ret = wait(&st);

            if(ret == -1) { //没有子进程了
                break;
            }

            if(WIFEXITED(st)) {
                // 是不是正常退出
                printf("退出的状态码：%d\n", WEXITSTATUS(st));
            }
            if(WIFSIGNALED(st)) {
                // 是不是异常终止
                printf("被哪个信号干掉了：%d\n", WTERMSIG(st));
            }

            printf("child die, pid = %d\n", ret);

            sleep(1);
        }

    } else if (pid == 0){
        // 子进程
        // while(1) { //不想让它一次性死掉
        printf("child, pid = %d\n",getpid());    
        sleep(1);       
        // }

        exit(0);//退出的状态码，一般会防止系统定义的宏
    }

    return 0; // exit(0)
}
```

使用`kill -9`的时候退出状态码为9。

```c
/*
    #include <sys/types.h>
    #include <sys/wait.h>
    pid_t waitpid(pid_t pid, int *wstatus, int options);
        功能：回收指定进程号的子进程，可以设置是否阻塞。
        参数：
            - pid:
                pid > 0 : 某个子进程的pid
                pid = 0 : 回收当前进程组的所有子进程，进程组一般需要成立的时候以自己为组长   
                pid = -1 : 回收所有的子进程，相当于 wait()  （最常用）
                pid < -1 : 某个进程组的组id的绝对值，回收指定进程组中的子进程，比如进程2需要回收，则设置为-2
            - options：设置阻塞或者非阻塞
                0 : 阻塞
                WNOHANG : 非阻塞
            - 返回值：
                > 0 : 返回子进程的id
                = 0 : options=WNOHANG, 表示还有子进程或者
                = -1 ：错误，或者没有子进程了
*/
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {

    // 有一个父进程，创建5个子进程（兄弟）
    pid_t pid;

    // 创建5个子进程
    for(int i = 0; i < 5; i++) {
        pid = fork();
        if(pid == 0) {
            break;
        }
    }

    if(pid > 0) {
        // 父进程
        while(1) {
            printf("parent, pid = %d\n", getpid());
            sleep(1);

            int st;
            // int ret = waitpid(-1, &st, 0);
            int ret = waitpid(-1, &st, WNOHANG);

            if(ret == -1) {
                break;
            } else if(ret == 0) {
                // 说明还有子进程存在，这样父进程就不必被挂起
                continue;
            } else if(ret > 0) {

                if(WIFEXITED(st)) {
                    // 是不是正常退出
                    printf("退出的状态码：%d\n", WEXITSTATUS(st));
                }
                if(WIFSIGNALED(st)) {
                    // 是不是异常终止
                    printf("被哪个信号干掉了：%d\n", WTERMSIG(st));
                }

                printf("child die, pid = %d\n", ret);
            }
           
        }

    } else if (pid == 0){
        // 子进程
         while(1) {
            printf("child, pid = %d\n",getpid());    
            sleep(1);       
         }
        exit(0);
    }

    return 0; 
}
```

## 进程通信

进程是一个独立的资源分配单元，不同进程（这里所说的进程通常指的是用户进程)之间的资源是独立的，没有关联。不能在一个进程中直接访问另一个进程的资源。但是，进程不是孤立的，不同的进程需要进行信息的交互和状态的传递等，因此需要进程间通信(IPC: Inter Processes Communication )。



进程间通信的目的：

- 数据传输：一个进程需要将它的数据发送给另一个进程。
- 通知事件：一个进程需要向另一个或一组进程发送消息，通知它（它们）发生了某种事件（如进程终止时要通知父进程)。
- 资源共享：多个进程之间共享同样的资源。为了做到这一点，需要内核提供互斥和同步机制。
- 进程控制：有些进程希望完全控制另一个进程的执行（如Debug进程)，此时控制进程希望能够拦截另一个进程的所有陷入和异常，并能够及时知道它的状态改变。



Linux下的进程通信：

1. 同一主机的进程间通信：
   - Unix进程的通信方式
     - 匿名管道
     - 有名管道
     - 信号
   - System V进程通信方式
     - 消息队列
     - 共享内存
     - 信号量
2. 不同主机（网络）进程间通信
   - Socket

### 匿名管道



管道也叫匿名管道，是`UNIX`系统`IPC`（进程间通信）的最古老形式，所有的`UNIX`系统都支持该通信机制。



统计一个目录的文件`ls | wc -l`，其中`l`为管道，为了执行该命令，`shell`创造了两个进程分别执行`ls`和`ws`。以`ls`进行`stdout(fd 1)`把信息写入管道（字节流、单向），再由`wc`进行`stdin(fd 0)`，都对应标准输入/输入/错误文件描述符的前三个的标准输入/输入。



管道（匿名/有名）特点：



1. 管道其实是一个在内核内存中维护的缓冲器，这个缓冲器的存储能力是有限的，不同的操作系统大小不一定相同。
2. 管道拥有文件的特质：读操作、写操作。管道的两端对应了两个文件描述符。匿名管道没有文件实体，有名管道有文件实体，但不存储数据。可以按照操作文件的方式对管道进行操作。
3. 一个管道是一个字节流，使用管道时不存在消息或者消息边界的概念，从管道读取数据的进程可以读取任意大小的数据块，而不管写入进程写入管道的数据块的大小是多少。
4. 通过管道传递的数据是顺序的，从管道中读取出来的字节的顺序和它们被写入管道的顺序是完全一样的。
5. 在管道中的数据的传递方向是单向的，一端用于写入，一端用于读取，管道是半双工的。
6. 从管道读数据是一次性操作，数据一旦被读走，它就从管道中被抛弃，释放空间以便写更多的数据，在管道中无法使用`lseek()`来随机的访问数据。
7. 匿名管道只能在具有公共祖先的进程（父进程与子进程，或者两个兄弟进程具有亲缘关系）之间使用。首先在`fork`后创建子进程后，两个进程的文件描述符是相同的。假设有某个文件描述符对应磁盘中的A文件，则父子进程都可以在一个文件操作。管道相当于一个文件，父进程共两个文件描述符分别对应管道的读/写端，而子进程也同有个文件描述符分别对应管道的读/写端，实现了半双工管道。



把数据放入进程1的缓冲区中`write`进管道，进程2把数据从管道`read`出来放入缓冲区。



管道的本质是一个循环队列，由读、写指针控制。

```c
/*
    #include <unistd.h>
    int pipe(int pipefd[2]);
        功能：创建一个匿名管道，用来进程间通信。
        参数：int pipefd[2] 这个数组是一个传出参数。
            pipefd[0] 对应的是管道的读端
            pipefd[1] 对应的是管道的写端
        返回值：
            成功 0
            失败 -1

    管道默认是阻塞的：如果管道中没有数据，read阻塞，如果管道满了，write阻塞

    注意：匿名管道只能用于具有关系的进程之间的通信（父子进程，兄弟进程）
*/

// 子进程发送数据给父进程，父进程读取到数据输出
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    // 在fork之前创建管道
    int pipefd[2];
    int ret = pipe(pipefd);
    if(ret == -1) {
        perror("pipe");
        exit(0);
    }

    // 创建子进程
    pid_t pid = fork();
    if(pid > 0) {
        // 父进程
        printf("i am parent process, pid : %d\n", getpid());

        // 关闭写端，实现半双工
        close(pipefd[1]);
        
        // 从管道的读取端读取数据
        char buf[1024] = {0};
        while(1) {
            int len = read(pipefd[0], buf, sizeof(buf));//读不需要等待，因为没有数据会阻塞
            printf("parent recv : %s, pid : %d\n", buf, getpid());
            
            // 向管道中写入数据
            //char * str = "hello,i am parent";
            //write(pipefd[1], str, strlen(str));
            //sleep(1);
        }

    } else if(pid == 0){
        // 子进程
        printf("i am child process, pid : %d\n", getpid());
        // 关闭读端，，实现半双工
        close(pipefd[0]);
        char buf[1024] = {0};
        while(1) {
            // 向管道中写入数据
            char * str = "hello,i am child";
            write(pipefd[1], str, strlen(str));
            //sleep(1);

            // int len = read(pipefd[0], buf, sizeof(buf));
            // printf("child recv : %s, pid : %d\n", buf, getpid());
            // bzero(buf, 1024);
        }
        
    }
    return 0;
}

```

```c
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    int pipefd[2];

    int ret = pipe(pipefd);

    // 获取管道的大小，_PC_PIPE_BUF为宏
    long size = fpathconf(pipefd[0], _PC_PIPE_BUF);

    printf("pipe size : %ld\n", size);

    return 0;
}
```

```shell
ulimit -a //查看管道大小
```

实现 `ps aux | grep xxx` 父子进程间通信.

```c
/*
    实现 ps aux | grep xxx 父子进程间通信
    
    子进程： ps aux, 子进程结束后，将数据发送给父进程
    父进程：获取到数据，过滤
    pipe()
    execlp()
    子进程将标准输出 stdout_fileno 重定向到管道的写端。  dup2
*/

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>

int main() {

    // 创建一个管道
    int fd[2];
    int ret = pipe(fd);

    if(ret == -1) {
        perror("pipe");
        exit(0);
    }

    // 创建子进程
    pid_t pid = fork();

    if(pid > 0) {
        // 父进程
        // 关闭写端
        close(fd[1]);
        // 从管道中读取
        char buf[1024] = {0};

        int len = -1;
        while((len = read(fd[0], buf, sizeof(buf) - 1)) > 0) {//字符串结束符去掉
            // 过滤数据输出
            printf("%s", buf);
            memset(buf, 0, 1024);
        }

        wait(NULL);

    } else if(pid == 0) {
        // 子进程
        // 关闭读端
        close(fd[0]);

        // 文件描述符的重定向 stdout_fileno -> fd[1]
        dup2(fd[1], STDOUT_FILENO);
        // 执行 ps aux
        execlp("ps", "ps", "aux", NULL);
        perror("execlp");
        exit(0);
    } else {
        perror("fork");
        exit(0);
    }


    return 0;
}
```



使用管道时，需要注意以下几种特殊的情况（假设都是阻塞I/O操作）

1. 所有的指向管道写端的文件描述符都关闭了（管道写端引用计数为0），有进程从管道的读端读数据，那么管道中剩余的数据被读取以后，再次read会返回0，就像读到文件末尾一样。
2. 如果有指向管道写端的文件描述符没有关闭（管道的写端引用计数大于0），而持有管道写端的进程也没有往管道中写数据，这个时候有进程从管道中读取数据，那么管道中剩余的数据被读取后，再次read会阻塞，直到管道中有数据可以读了才读取数据并返回。

3. 如果所有指向管道读端的文件描述符都关闭了（管道的读端引用计数为0），这个时候有进程向管道中写数据，那么该进程会收到一个信号SIGPIPE, 通常会导致进程异常终止。
4. 如果有指向管道读端的文件描述符没有关闭（管道的读端引用计数大于0），而持有管道读端的进程也没有从管道中读数据，这时有进程向管道中写数据，那么在管道被写满的时候再次write会阻塞，直到管道中有空位置才能再次写入数据并返回。

总结：

- 读管道：
  - 管道中有数据，read返回实际读到的字节数。
  - 管道中无数据：
    - 写端被全部关闭，read返回0（相当于读到文件的末尾）
                  写端没有完全关闭，read阻塞等待
- 写管道：
  - 管道读端全部被关闭，进程异常终止（进程收到SIGPIPE信号）
  - 管道读端没有全部关闭：
    - 管道已满，write阻塞
    - 管道没有满，write将数据写入，并返回实际写入的字节数

设置为非阻塞状态下的`read()`

```c
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
/*
    设置管道非阻塞
    int flags = fcntl(fd[0], F_GETFL);  // 获取原来的flag
    flags |= O_NONBLOCK;            // 修改flag的值
    fcntl(fd[0], F_SETFL, flags);   // 设置新的flag
*/
int main() {

    // 在fork之前创建管道
    int pipefd[2];
    int ret = pipe(pipefd);
    if(ret == -1) {
        perror("pipe");
        exit(0);
    }

    // 创建子进程
    pid_t pid = fork();
    if(pid > 0) {
        // 父进程
        printf("i am parent process, pid : %d\n", getpid());

        // 关闭写端
        close(pipefd[1]);
        
        // 从管道的读取端读取数据
        char buf[1024] = {0};

        int flags = fcntl(pipefd[0], F_GETFL);  // 获取原来的flag
        flags |= O_NONBLOCK;            // 修改flag的值
        fcntl(pipefd[0], F_SETFL, flags);   // 设置新的flag

        while(1) {
            int len = read(pipefd[0], buf, sizeof(buf));
            printf("len : %d\n", len);
            printf("parent recv : %s, pid : %d\n", buf, getpid());
            memset(buf, 0, 1024);
            sleep(1);
        }

    } else if(pid == 0){
        // 子进程
        printf("i am child process, pid : %d\n", getpid());
        // 关闭读端
        close(pipefd[0]);
        char buf[1024] = {0};
        while(1) {
            // 向管道中写入数据
            char * str = "hello,i am child";
            write(pipefd[1], str, strlen(str));
            sleep(5);
        }
        
    }
    return 0;
}
```

### 有名管道



有名管道(`FIFO`)不同于匿名管道之处在于它提供了一个路径名与之关联，以`FIFO`的文件形式存在于文件系统中，并且其打开方式与打开一个普通文件是一样的，这样即使与`FIFO` 的创建进程不存在亲缘关系的进程，只要可以访问该路径，就能够彼此通过`FIFO`相互通信，因此,通过`FIFO`不相关的进程也能交换数据。



一旦打开了 FIFO，就能在它上面使用与操作匿名管道和其他文件的系统调用一样的I/O系统调用了(如`read ( )`、 `write ( )`和`close ( )`)。与管道一样, `FIFO`也有一个写入端和读取端，并且从管道中读取数据的顺序与写入的顺序是一样的。FIFO 的名称也由此而来：先入先出。



本质上也是一个循环队列。



有名管道与匿名管道的区别。有名管道(`FIFO`)和匿名管道(`pipe`)有一些特点是相同的，不一样的地方在于:

1. `FIFO`在文件系统中作为一个特殊文件存在，但`FIFO`中的内容却存放在内存中。
1. 当使用`FIFO`的进程退出后， `FIFO`文件将继续保存在文件系统中以便以后使用。
1. `FIFO` 有名字，不相关的进程可以通过打开有名管道进行通信。



有名管道的使用：

1. 通过命令创建有名管道：`mkfifo FIFOfileName`

2. 通过函数创建有名管道：

   ```c
   #include <sys/types.h>#include <sys/ stat.h>
   int mkfifo (const char *pathname,mode_t mode) ;
   ```

   ```c
   /*
       创建fifo文件
       1.通过命令： mkfifo 名字
       2.通过函数：int mkfifo(const char *pathname, mode_t mode);
   
       #include <sys/types.h>
       #include <sys/stat.h>
       int mkfifo(const char *pathname, mode_t mode);
           参数：
               - pathname: 管道名称的路径
               - mode: 文件的权限 和 open 的 mode 是一样的
                       是一个八进制的数
           返回值：成功返回0，失败返回-1，并设置错误号
   
   */
   
   #include <stdio.h>
   #include <sys/types.h>
   #include <sys/stat.h>
   #include <stdlib.h>
   #include <unistd.h>
   
   int main() {
   
   
       // 判断文件是否存在
       int ret = access("fifo1", F_OK);
       if(ret == -1) {
           printf("管道不存在，创建管道\n");
           
           ret = mkfifo("fifo1", 0664);
   
           if(ret == -1) {
               perror("mkfifo");
               exit(0);
           }       
       }
       return 0;
   }
   ```

   



一旦使用`mkfifo`创建了一个`FIFO`，就可以使用`open`打开它，常见的文件I/o函数都可用于`fifo`。如: `close`、`read`、`write`、`unlink`等。



实现有名管道机制。

```c
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

// 从管道中读取数据
int main() {

    // 1.打开管道文件
    int fd = open("test", O_RDONLY);
    if(fd == -1) {
        perror("open");
        exit(0);
    }

    // 读数据
    while(1) {
        char buf[1024] = {0};
        int len = read(fd, buf, sizeof(buf));
        if(len == 0) {
            printf("写端断开连接了...\n");
            break;
        }
        printf("recv buf : %s\n", buf);
    }

    close(fd);

    return 0;
}
```

```c
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

// 向管道中写数据
/*
    有名管道的注意事项：
        1.一个为只读而打开一个管道的进程会阻塞，直到另外一个进程为只写打开管道
        2.一个为只写而打开一个管道的进程会阻塞，直到另外一个进程为只读打开管道

    读管道：
        管道中有数据，read返回实际读到的字节数
        管道中无数据：
            管道写端被全部关闭，read返回0，（相当于读到文件末尾）
            写端没有全部被关闭，read阻塞等待
    
    写管道：
        管道读端被全部关闭，进行异常终止（收到一个SIGPIPE信号）
        管道读端没有全部关闭：
            管道已经满了，write会阻塞
            管道没有满，write将数据写入，并返回实际写入的字节数。
*/
int main() {

    // 1.判断文件是否存在
    int ret = access("test", F_OK);
    if(ret == -1) {
        printf("管道不存在，创建管道\n");
        
        // 2.创建管道文件
        ret = mkfifo("test", 0664);

        if(ret == -1) {
            perror("mkfifo");
            exit(0);
        }       

    }

    // 3.以只写的方式打开管道
    int fd = open("test", O_WRONLY);
    if(fd == -1) {
        perror("open");
        exit(0);
    }

    // 写数据
    for(int i = 0; i < 100; i++) {
        char buf[1024];
        sprintf(buf, "hello, %d\n", i);
        printf("write data : %s\n", buf);
        write(fd, buf, strlen(buf));
        sleep(1);
    }

    close(fd);

    return 0;
}
```

利用管道实现简易聊天功能，下面介绍设计思想。

1. 创建两个管道。
2. 进程A：
   - 以只写打开管道
   - 以只读打开管道
   - 循环写读数据
3. 进程B（与A相反，否则会阻塞）:
   - 以只读打开管道
   - 以只写打开管道
   - 循环读写数据

```c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main() {

    // 1.判断有名管道文件是否存在
    int ret = access("fifo1", F_OK);
    if(ret == -1) {
        // 文件不存在
        printf("管道不存在，创建对应的有名管道\n");
        ret = mkfifo("fifo1", 0664);
        if(ret == -1) {
            perror("mkfifo");
            exit(0);
        }
    }

    ret = access("fifo2", F_OK);
    if(ret == -1) {
        // 文件不存在
        printf("管道不存在，创建对应的有名管道\n");
        ret = mkfifo("fifo2", 0664);
        if(ret == -1) {
            perror("mkfifo");
            exit(0);
        }
    }

    // 2.以只写的方式打开管道fifo1
    int fdw = open("fifo1", O_WRONLY);
    if(fdw == -1) {
        perror("open");
        exit(0);
    }
    printf("打开管道fifo1成功，等待写入...\n");
    // 3.以只读的方式打开管道fifo2
    int fdr = open("fifo2", O_RDONLY);
    if(fdr == -1) {
        perror("open");
        exit(0);
    }
    printf("打开管道fifo2成功，等待读取...\n");

    char buf[128];

    // 4.循环的写读数据
    while(1) {
        memset(buf, 0, 128);
        // 获取标准输入的数据
        fgets(buf, 128, stdin);
        // 写数据
        ret = write(fdw, buf, strlen(buf));
        if(ret == -1) {
            perror("write");
            exit(0);
        }

        // 5.读管道数据
        memset(buf, 0, 128);
        ret = read(fdr, buf, 128);
        if(ret <= 0) {
            perror("read");
            break;
        }
        printf("buf: %s\n", buf);
    }

    // 6.关闭文件描述符
    close(fdr);
    close(fdw);

    return 0;
}
```

```c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main() {

    // 1.判断有名管道文件是否存在
    int ret = access("fifo1", F_OK);
    if(ret == -1) {
        // 文件不存在
        printf("管道不存在，创建对应的有名管道\n");
        ret = mkfifo("fifo1", 0664);
        if(ret == -1) {
            perror("mkfifo");
            exit(0);
        }
    }

    ret = access("fifo2", F_OK);
    if(ret == -1) {
        // 文件不存在
        printf("管道不存在，创建对应的有名管道\n");
        ret = mkfifo("fifo2", 0664);
        if(ret == -1) {
            perror("mkfifo");
            exit(0);
        }
    }

    // 2.以只读的方式打开管道fifo1
    int fdr = open("fifo1", O_RDONLY);
    if(fdr == -1) {
        perror("open");
        exit(0);
    }
    printf("打开管道fifo1成功，等待读取...\n");
    // 3.以只写的方式打开管道fifo2
    int fdw = open("fifo2", O_WRONLY);
    if(fdw == -1) {
        perror("open");
        exit(0);
    }
    printf("打开管道fifo2成功，等待写入...\n");

    char buf[128];

    // 4.循环的读写数据
    while(1) {
        // 5.读管道数据
        memset(buf, 0, 128);
        ret = read(fdr, buf, 128);
        if(ret <= 0) {
            perror("read");
            break;
        }
        printf("buf: %s\n", buf);

        memset(buf, 0, 128);
        // 获取标准输入的数据
        fgets(buf, 128, stdin);
        // 写数据
        ret = write(fdw, buf, strlen(buf));
        if(ret == -1) {
            perror("write");
            exit(0);
        }
    }

    // 6.关闭文件描述符
    close(fdr);
    close(fdw);

    return 0;
}
```

考虑阻塞情况，只能实现一发一收。如果想要一直读一直写，则把读写放入不同进程（在父进程读、子进程写/父进程写，子进程读）当中。

### 内存映射

内存映射(Memory-mapped I/o）是将磁盘文件的数据映射到内存，用户通过修改内存就能修改磁盘文件。



![image-20240324163827081](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240324163827081.png)



其实是映射到动态库加载的区域，内存中保存的文件的数据，`off`是文件的偏移量，`len`是映射数据长度。

```c
#include <sys / mman.h>
void *mmap(void *addr,size_t length,int prot, int flagint fd, off_t offset) ;
int munmap (void *addr,size_t length);
```

```c
/*
    #include <sys/mman.h>
    void *mmap(void *addr, size_t length, int prot, int flags,int fd, off_t offset);
        - 功能：将一个文件或者设备的数据映射到内存中
        - 参数：
            - void *addr: NULL, 由内核指定
            - length : 要映射的数据的长度，这个值不能为0。建议使用文件的长度。假如没有到分页大小则也分配一个页的整数倍。
                    获取文件的长度：stat lseek
            - prot : 对申请的内存映射区的操作权限
                -PROT_EXEC ：可执行的权限
                -PROT_READ ：读权限
                -PROT_WRITE ：写权限
                -PROT_NONE ：没有权限
                要操作映射内存，必须要有读的权限。
                PROT_READ、PROT_READ|PROT_WRITE
            - flags :
                - MAP_SHARED : 映射区的数据会自动和磁盘文件进行同步，进程间通信，必须要设置这个选项
                - MAP_PRIVATE ：不同步，内存映射区的数据改变了，对原来的文件不会修改，会重新创建一个新的文件。（copy on write）
            - fd: 需要映射的那个文件的文件描述符
                - 通过open得到，open的是一个磁盘文件
                - 注意：文件的大小不能为0，open指定的权限不能和prot参数有冲突（prot权限小于等于open权限且必须有read权限，最好保持一致）：
                    prot: PROT_READ                open:只读/读写 
                    prot: PROT_READ | PROT_WRITE   open:读写
            - offset：偏移量，一般不用。必须指定的是4k的整数倍，0表示不偏移。
        - 返回值：返回创建的内存的首地址
            失败返回MAP_FAILED，(void *) -1

    int munmap(void *addr, size_t length);
        - 功能：释放内存映射
        - 参数：
            - addr : 要释放的内存的首地址
            - length : 要释放的内存的大小，要和mmap函数中的length参数的值一样。
*/

/*
    使用内存映射实现进程间通信：
    1.有关系的进程（父子进程）
        - 还没有子进程的时候
            - 通过唯一的父进程，先创建内存映射区
        - 有了内存映射区以后，创建子进程
        - 父子进程共享创建的内存映射区
    
    2.没有关系的进程间通信
        - 准备一个大小不是0的磁盘文件
        - 进程1 通过磁盘文件创建内存映射区
            - 得到一个操作这块内存的指针
        - 进程2 通过磁盘文件创建内存映射区
            - 得到一个操作这块内存的指针
        - 使用内存映射区通信

    注意：内存映射区通信，是非阻塞。
*/

#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <wait.h>

// 作业:使用内存映射实现没有关系的进程间的通信。
int main() {

    // 1.打开一个文件
    int fd = open("test.txt", O_RDWR);
    int size = lseek(fd, 0, SEEK_END);  // 获取文件的大小

    // 2.创建内存映射区
    void *ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(ptr == MAP_FAILED) {
        perror("mmap");
        exit(0);
    }

    // 3.创建子进程
    pid_t pid = fork();
    if(pid > 0) {
        wait(NULL);//回收子进程
        // 父进程
        char buf[64];
        strcpy(buf, (char *)ptr);
        printf("read data : %s\n", buf);
       
    }else if(pid == 0){
        // 子进程
        strcpy((char *)ptr, "nihao a, son!!!");
    }

    // 关闭内存映射区
    munmap(ptr, size);

    return 0;
}
```

如果是不同进程，则把读写分开放入两个即可。内核是保证没有关系的进程对同一文件mmap能够得到指向同一块内存映射区的指针。另外两个不同的进程对同一块内存进行操作读写保证互斥访问。



思考：

1. 如果对mmap的返回值(ptr)做++操作(ptr++ )，munmap是否能够成功?
   - 可以但是不建议，因为会munmap的释放需要原先数值

2. 如果open时O_RDONLY，mmap时prot参数指定PROT_READ | PROT_WRITE会怎样?
   - 错误，返回MAP_FAILED，prot权限小于等于open权限且必须有read权限。

3. 如果文件偏移量为1000会怎样?
   - 必须是4K的整数倍，返回MAP_FAILED

4. mmap什么情况下会调用失败?
   - length=0
   - prot只指定写权限
   - prot权限小于等于open权限且必须有read权限

5. 可以open的时候O_CREAT一个新文件来创建映射区吗?
   - 可以的，但创建文件的大小必须大于0，可以对文件大小进行扩展`lseek`或者`truncate`

6. mmap后关闭文件描述符，对mmap映射有没有影响?
   - 不会产生问题，映射区还在，创建映射区的fd被关闭
7. 对ptr越界操作会怎样?
   - 非法访问内存产生段错误



使用系统映射实现文件拷贝的功能。

```c
// 使用内存映射实现文件拷贝的功能
/*
    思路：
        1.对原始的文件进行内存映射
        2.创建一个新文件（拓展该文件）
        3.把新文件的数据映射到内存中
        4.通过内存拷贝将第一个文件的内存数据拷贝到新的文件内存中
        5.释放资源
*/
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main() {

    // 1.对原始的文件进行内存映射
    int fd = open("english.txt", O_RDWR);
    if(fd == -1) {
        perror("open");
        exit(0);
    }

    // 获取原始文件的大小
    int len = lseek(fd, 0, SEEK_END);

    // 2.创建一个新文件（拓展该文件）
    int fd1 = open("cpy.txt", O_RDWR | O_CREAT, 0664);
    if(fd1 == -1) {
        perror("open");
        exit(0);
    }
    
    // 对新创建的文件进行拓展
    truncate("cpy.txt", len);
    write(fd1, " ", 1);

    // 3.分别做内存映射
    void * ptr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    void * ptr1 = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd1, 0);

    if(ptr == MAP_FAILED) {
        perror("mmap");
        exit(0);
    }

    if(ptr1 == MAP_FAILED) {
        perror("mmap");
        exit(0);
    }

    // 内存拷贝
    memcpy(ptr1, ptr, len);
    
    // 释放资源
    munmap(ptr1, len);
    munmap(ptr, len);

    close(fd1);
    close(fd);

    return 0;
}
```

没有文件实体的映射，即只能是父子关系的映射，即匿名映射。

```c
/*
    匿名映射：不需要文件实体进程一个内存映射
*/

#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {

    // 1.创建匿名内存映射区
    int len = 4096;
    void * ptr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);//匿名指定-1
    if(ptr == MAP_FAILED) {
        perror("mmap");
        exit(0);
    }

    // 父子进程间通信
    pid_t pid = fork();

    if(pid > 0) {
        // 父进程
        strcpy((char *) ptr, "hello, world");
        wait(NULL);
    }else if(pid == 0) {
        // 子进程
        sleep(1);
        printf("%s\n", (char *)ptr);
    }

    // 释放内存映射区
    int ret = munmap(ptr, len);

    if(ret == -1) {
        perror("munmap");
        exit(0);
    }
    return 0;
}
```

### 信号

信号是 Linux进程间通信的最古老的方式之一，是事件发生时对进程的通知机制，有时也称之为软件中断，它是在软件层次上对中断机制的一种模拟，是一种异步通信的方式。信号可以导致一个正在运行的进程被另一个正在运行的异步进程中断转而处理某一个突发事件。



发往进程的诸多信号，通常都是源于内核。引发内核为进程产生信号的各类事件如下:

1. 对于前台进程，用户可以通过输入特殊的终端字符来给它发送信号。比如输入Ctrl+C，通常会给进程发送一个中断信号。
2. 硬件发生异常，即硬件检测到一个错误条件并通知内核，随即再由内核发送相应信号给相关进程。比如执行一条异常的机器语言指令，诸如被0除，或者引用了无法访问的内存区域。
3. 系统状态变化，比如alarm定时器到期将引起SIGALRM信号，进程执行的CPU时间超限，或者该进程的某个子进程退出。
4. 运行kill命令或调用kill函数。
   

使用信号的两个主要目的是:

1. 让进程知道已经发生了一个特定的事情。
2. 强迫进程执行它自己代码中的信号处理程序。

信号的特点:

1. 简单
2. 不能携带大量信息
3. 满足某个特定条件才发送优先级比较高
4. 查看系统定义的信号列表:kill -l
5. 前31个信号为常规信号，其余为实时信号。



下面这些信号是必须要掌握的信号信息。

| **2**  | **SIGINT**  | **当用户按下了 `Ctrl+C` 组合键时，用户终端向正在运行中的由该终端启动的程序发出此信号** | **终止进程**                                                 |
| ------ | ----------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| **3**  | **SIGQUIT** | **用户按下 `Ctrl+\` 组合键时产生该信号，用户终端向正在运行中的由该终端启动的程序发出些信号** | **终止进程**                                                 |
| **9**  | **SIGKILL** | **无条件终止进程。该信号不能被忽略，处理和阻塞**             | **终止进程，可以杀死任何正常进程（僵尸进程等异常进程不算）** |
| **11** | **SIGSEGV** | **指示进程进行了无效内存访问(段错误)**                       | **终止进程并产生core文件**                                   |
| **13** | **SIGPIPE** | **Broken pipe 向一个没有读端的管道写数据**                   | **终止进程**                                                 |
| **17** | **SIGCHLD** | **子进程结束时，父进程会收到这个信号**                       | **忽略这个信号**                                             |
| **18** | **SIGCONT** | **如果进程已停止，则使其继续运行**                           | **继续/忽略**                                                |
| **19** | **SIGSTOP** | **停止进程的执行。信号不能被忽略，处理和阻塞**               | **为终止进程**                                               |



信号的5中默认处理动作：

- `Term`：终止进程；
- `Ign`：当前进程忽略掉这个信号；
- `Core`：终止进程，并生成一个core文件；
- `Stop`：暂停当前进程；
- `Cont`：继续执行当前被暂停的进程；



信号的几种状态：产生、未决、递达；



`SIGKILL`和`SIGSTOP`信号不能被捕捉、阻塞或者忽略，只能执行默认动作。



```c
/*  
    #include <sys/types.h>
    #include <signal.h>

    int kill(pid_t pid, int sig);
        - 功能：给任何的进程或者进程组pid, 发送任何的信号 sig
        - 参数：
            - pid ：
                > 0 : 将信号发送给指定的进程
                = 0 : 将信号发送给当前的进程组
                = -1 : 将信号发送给每一个有权限接收这个信号的进程
                < -1 : 这个pid=某个进程组的ID取反 （-12345）
            - sig : 需要发送的信号的编号或者是宏值，0表示不发送任何信号

        kill(getppid(), 9);
        kill(getpid(), 9);
        
    int raise(int sig);
        - 功能：给当前进程发送信号
        - 参数：
            - sig : 要发送的信号
        - 返回值：
            - 成功 0
            - 失败 非0
        kill(getpid(), sig);   

    void abort(void);
        - 功能： 发送SIGABRT信号给当前的进程，杀死当前进程
        kill(getpid(), SIGABRT);
*/

#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

int main() {

    pid_t pid = fork();

    if(pid == 0) {
        // 子进程
        int i = 0;
        for(i = 0; i < 5; i++) {
            printf("child process\n");
            sleep(1);
        }

    } else if(pid > 0) {
        // 父进程
        printf("parent process\n");
        sleep(2);
        printf("kill child process now\n");
        kill(pid, SIGINT);
    }

    return 0;
}
```

```c
/*
    #include <unistd.h>
    unsigned int alarm(unsigned int seconds);
        - 功能：设置定时器（闹钟）。函数调用，开始倒计时，当倒计时为0的时候，
                函数会给当前的进程发送一个信号：SIGALARM
        - 参数：
            seconds: 倒计时的时长，单位：秒。如果参数为0，定时器无效（不进行倒计时，不发信号）。
                    取消一个定时器，通过alarm(0)。
        - 返回值：
            - 之前没有定时器，返回0
            - 之前有定时器，返回之前的定时器剩余的时间

    - SIGALARM ：默认终止当前的进程，每一个进程都有且只有唯一的一个定时器。
        alarm(10);  -> 返回0
        过了1秒
        alarm(5);   -> 返回9

    alarm(100) -> 该函数是不阻塞的
*/

#include <stdio.h>
#include <unistd.h>

int main() {

    int seconds = alarm(5);
    printf("seconds = %d\n", seconds);  // 0

    sleep(2);
    seconds = alarm(2);    // 不阻塞
    printf("seconds = %d\n", seconds);  // 3

    while(1) {
    }

    return 0;
}
```

```c
// 1秒钟电脑能数多少个数？
#include <stdio.h>
#include <unistd.h>

/*
    实际的时间 = 内核时间 + 用户时间 + 消耗的时间
    进行文件IO操作的时候比较浪费时间

    定时器，与进程的状态无关（自然定时法）。无论进程处于什么状态，alarm都会计时。
*/

int main() {    

    alarm(1);

    int i = 0;
    while(1) {
        printf("%i\n", i++);
    }

    return 0;
}
```

```c
/*
    #include <sys/time.h>
    int setitimer(int which, const struct itimerval *new_value,
                        struct itimerval *old_value);
    
        - 功能：设置定时器（闹钟）。可以替代alarm函数。精度微妙us，可以实现周期性定时
        - 参数：
            - which : 定时器以什么时间计时
              ITIMER_REAL: 实际的时间，真实时间，时间到达，发送 SIGALRM   常用
              ITIMER_VIRTUAL: 用户时间，时间到达，发送 SIGVTALRM
              ITIMER_PROF: 以该进程在用户态和内核态下所消耗的时间来计算，时间到达，发送 SIGPROF

            - new_value: 设置定时器的属性
            
                struct itimerval {      // 定时器的结构体
                struct timeval it_interval;  // 每个阶段的时间，间隔时间
                struct timeval it_value;     // 延迟多长时间执行定时器
                };

                struct timeval {        // 时间的结构体
                    time_t      tv_sec;     //  秒数     
                    suseconds_t tv_usec;    //  微秒    
                };

            过10秒后，每个2秒定时一次
           
            - old_value ：记录上一次的定时的时间参数，一般不使用，指定NULL
        
        - 返回值：
            成功 0
            失败 -1 并设置错误号
*/

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

// 过3秒以后，每隔2秒钟定时一次
int main() {

    struct itimerval new_value;

    // 设置间隔的时间
    new_value.it_interval.tv_sec = 2;
    new_value.it_interval.tv_usec = 0;

    // 设置延迟的时间,3秒之后开始第一次定时，注意是第一次
    new_value.it_value.tv_sec = 3;
    new_value.it_value.tv_usec = 0;


    int ret = setitimer(ITIMER_REAL, &new_value, NULL); // 非阻塞的
    printf("定时器开始了...\n");

    if(ret == -1) {
        perror("setitimer");
        exit(0);
    }

    getchar();

    return 0;
}
```

```c
/*
    #include <signal.h>
    typedef void (*sighandler_t)(int);
    sighandler_t signal(int signum, sighandler_t handler);
        - 功能：设置某个信号的捕捉行为
        - 参数：
            - signum: 要捕捉的信号
            - handler: 捕捉到信号要如何处理
                - SIG_IGN ： 忽略信号
                - SIG_DFL ： 使用信号默认的行为
                - 回调函数 :  这个函数是内核调用，程序员只负责写，捕捉到信号后如何去处理信号。
                回调函数：
                    - 需要程序员实现，提前准备好的，函数的类型根据实际需求，看函数指针的定义
                    - 不是程序员调用，而是当信号产生，由内核调用
                    - 函数指针是实现回调的手段，函数实现之后，将函数名放到函数指针的位置就可以了。

        - 返回值：
            成功，返回上一次注册的信号处理函数的地址。第一次调用返回NULL
            失败，返回SIG_ERR，设置错误号
            
    SIGKILL SIGSTOP不能被捕捉，不能被忽略。
*/

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void myalarm(int num) {
    printf("捕捉到了信号的编号是：%d\n", num);
    printf("xxxxxxx\n");
}

// 过3秒以后，每隔2秒钟定时一次
int main() {

    // 注册信号捕捉，写在前面，不然怎么捕捉
    // signal(SIGALRM, SIG_IGN);
    // signal(SIGALRM, SIG_DFL);
    // void (*sighandler_t)(int); 函数指针，int类型的参数表示捕捉到的信号的值。
    signal(SIGALRM, myalarm);

    struct itimerval new_value;

    // 设置间隔的时间
    new_value.it_interval.tv_sec = 2;
    new_value.it_interval.tv_usec = 0;

    // 设置延迟的时间,3秒之后开始第一次定时
    new_value.it_value.tv_sec = 3;
    new_value.it_value.tv_usec = 0;

    int ret = setitimer(ITIMER_REAL, &new_value, NULL); // 非阻塞的
    printf("定时器开始了...\n");

    if(ret == -1) {
        perror("setitimer");
        exit(0);
    }

    getchar();

    return 0;
}
```

许多信号相关的系统调用都需要能表示一组不同的信号，多个信号可使用一个称之为信号集的数据结构来表示，其系统数据类型为`sigset_t`。



在PCB中有两个非常重要的信号集。一个称之为“阻塞信号集”，另一个称之为“未决信号集”。这两个信号集都是内核使用位图机制（二进制位的或）来实现的。但操作系统不允许我们直接对这两个信号集进行位操作。而需自定义另外一个集合，借助信号集操作函数来对PCB中的这两个信号集进行修改。



信号的“未决”是―种状态，指的是从信号的产生到信号被处理前的这一段时间。信号的“阻塞”是一个开关动作，指的是阻止信号被处理，但不是阻止信号产生。

信号的阻塞就是让系统暂时保留信号留待以后发送。由于另外有办法让系统忽略信号。所以一般情况下信号的阻塞只是暂时的，只是为了防止信号打断敏感的操作。

```c
/*
    以下信号集相关的函数都是对自定义的信号集进行操作。

    int sigemptyset(sigset_t *set);
        - 功能：清空信号集中的数据,将信号集中的所有的标志位置为0
        - 参数：set,传出参数，需要操作的信号集
        - 返回值：成功返回0， 失败返回-1

    int sigfillset(sigset_t *set);
        - 功能：将信号集中的所有的标志位置为1
        - 参数：set,传出参数，需要操作的信号集
        - 返回值：成功返回0， 失败返回-1

    int sigaddset(sigset_t *set, int signum);
        - 功能：设置信号集中的某一个信号对应的标志位为1，表示阻塞这个信号
        - 参数：
            - set：传出参数，需要操作的信号集
            - signum：需要设置阻塞的那个信号
        - 返回值：成功返回0， 失败返回-1

    int sigdelset(sigset_t *set, int signum);
        - 功能：设置信号集中的某一个信号对应的标志位为0，表示不阻塞这个信号
        - 参数：
            - set：传出参数，需要操作的信号集
            - signum：需要设置不阻塞的那个信号
        - 返回值：成功返回0， 失败返回-1

    int sigismember(const sigset_t *set, int signum);
        - 功能：判断某个信号是否阻塞
        - 参数：
            - set：需要操作的信号集
            - signum：需要判断的那个信号
        - 返回值：
            1 ： signum被阻塞
            0 ： signum不阻塞
            -1 ： 失败

*/

#include <signal.h>
#include <stdio.h>

int main() {

    // 创建一个信号集
    sigset_t set;

    // 清空信号集的内容
    sigemptyset(&set);

    // 判断 SIGINT 是否在信号集 set 里
    int ret = sigismember(&set, SIGINT);
    if(ret == 0) {
        printf("SIGINT 不阻塞\n");
    } else if(ret == 1) {
        printf("SIGINT 阻塞\n");
    }

    // 添加几个信号到信号集中
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGQUIT);

    // 判断SIGINT是否在信号集中
    ret = sigismember(&set, SIGINT);
    if(ret == 0) {
        printf("SIGINT 不阻塞\n");
    } else if(ret == 1) {
        printf("SIGINT 阻塞\n");
    }

    // 判断SIGQUIT是否在信号集中
    ret = sigismember(&set, SIGQUIT);
    if(ret == 0) {
        printf("SIGQUIT 不阻塞\n");
    } else if(ret == 1) {
        printf("SIGQUIT 阻塞\n");
    }

    // 从信号集中删除一个信号
    sigdelset(&set, SIGQUIT);

    // 判断SIGQUIT是否在信号集中
    ret = sigismember(&set, SIGQUIT);
    if(ret == 0) {
        printf("SIGQUIT 不阻塞\n");
    } else if(ret == 1) {
        printf("SIGQUIT 阻塞\n");
    }

    return 0;
}
```

1、用户通过键盘  Ctrl + C, 产生2号信号SIGINT (信号被创建)

2、信号产生但是没有被处理 （未决）

    - 在内核中将所有的没有被处理的信号存储在一个集合中 （未决信号集）
        - SIGINT信号状态被存储在第二个标志位上
        - 这个标志位的值为0， 说明信号不是未决状态
        - 这个标志位的值为1， 说明信号处于未决状态

3、这个未决状态的信号，需要被处理，处理之前需要和另一个信号集（阻塞信号集），进行比较

    - 阻塞信号集默认不阻塞任何的信号
        - 如果想要阻塞某些信号需要用户调用系统的API

4、在处理的时候和阻塞信号集中的标志位进行查询，看是不是对该信号设置阻塞了

    - 如果没有阻塞，这个信号就被处理
        - 如果阻塞了，这个信号就继续处于未决状态，直到阻塞解除，这个信号就被处理

```c
/*
    int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
        - 功能：将自定义信号集中的数据设置到内核中（设置阻塞，解除阻塞，替换）
        - 参数：
            - how : 如何对内核阻塞信号集进行处理
                SIG_BLOCK: 将用户设置的阻塞信号集添加到内核中，内核中原来的数据不变
                    假设内核中默认的阻塞信号集是mask， mask | set
                SIG_UNBLOCK: 根据用户设置的数据，对内核中的数据进行解除阻塞
                    mask &= ~set
                SIG_SETMASK:覆盖内核中原来的值
            
            - set ：已经初始化好的用户自定义的信号集
            - oldset : 保存设置之前的内核中的阻塞信号集的状态，可以是 NULL
        - 返回值：
            成功：0
            失败：-1
                设置错误号：EFAULT、EINVAL

    int sigpending(sigset_t *set);
        - 功能：获取内核中的未决信号集
        - 参数：set,传出参数，保存的是内核中的未决信号集中的信息。
*/

// 编写一个程序，把所有的常规信号（1-31）的未决状态打印到屏幕
// 设置某些信号是阻塞的，通过键盘产生这些信号

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int main() {

    // 设置2、3号信号阻塞
    sigset_t set;
    sigemptyset(&set);
    // 将2号和3号信号添加到信号集中
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGQUIT);

    // 修改内核中的阻塞信号集
    sigprocmask(SIG_BLOCK, &set, NULL);

    int num = 0;

    while(1) {
        num++;
        // 获取当前的未决信号集的数据
        sigset_t pendingset;
        sigemptyset(&pendingset);
        sigpending(&pendingset);

        // 遍历前32位
        for(int i = 1; i <= 31; i++) {
            if(sigismember(&pendingset, i) == 1) {
                printf("1");
            }else if(sigismember(&pendingset, i) == 0) {
                printf("0");
            }else {
                perror("sigismember");
                exit(0);
            }
        }

        printf("\n");
        sleep(1);
        if(num == 10) {
            // 解除阻塞
            sigprocmask(SIG_UNBLOCK, &set, NULL);
        }

    }


    return 0;
}
```

```c
/*
    #include <signal.h>
    int sigaction(int signum, const struct sigaction *act,
                            struct sigaction *oldact);//推荐

        - 功能：检查或者改变信号的处理。信号捕捉
        - 参数：
            - signum : 需要捕捉的信号的编号或者宏值（信号的名称）,更推荐使用宏值
            - act ：捕捉到信号之后的处理动作
            - oldact : 上一次对信号捕捉相关的设置，一般不使用，传递NULL
        - 返回值：
            成功 0
            失败 -1

     struct sigaction {
        // 函数指针，指向的函数就是信号捕捉到之后的处理函数
        void     (*sa_handler)(int);
        // 不常用
        void     (*sa_sigaction)(int, siginfo_t *, void *);
        // 临时阻塞信号集，在信号捕捉函数执行过程中，临时阻塞某些信号。
        sigset_t   sa_mask;
        // 使用哪一个信号处理对捕捉到的信号进行处理
        // 这个值可以是0，表示使用sa_handler,也可以是SA_SIGINFO表示使用sa_sigaction（最常用的两个）
        int        sa_flags;
        // 被废弃掉了
        void     (*sa_restorer)(void);
    };

*/
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void myalarm(int num) {
    printf("捕捉到了信号的编号是：%d\n", num);
    printf("xxxxxxx\n");
}

// 过3秒以后，每隔2秒钟定时一次
int main() {

    struct sigaction act;
    act.sa_flags = 0;
    act.sa_handler = myalarm;
    sigemptyset(&act.sa_mask);  // 清空临时阻塞信号集
   
    // 注册信号捕捉
    sigaction(SIGALRM, &act, NULL);

    struct itimerval new_value;

    // 设置间隔的时间
    new_value.it_interval.tv_sec = 2;
    new_value.it_interval.tv_usec = 0;

    // 设置延迟的时间,3秒之后开始第一次定时
    new_value.it_value.tv_sec = 3;
    new_value.it_value.tv_usec = 0;

    int ret = setitimer(ITIMER_REAL, &new_value, NULL); // 非阻塞的
    printf("定时器开始了...\n");

    if(ret == -1) {
        perror("setitimer");
        exit(0);
    }

    // getchar();
    while(1);

    return 0;
}
```

![image-20240326214525843](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240326214525843.png)



在执行信号处理函数的时候，假如再次接收当前未决信号，则该新信号会被阻塞，该未决在执行信号处理函数的时候值为0，新信号进入置为1，但是新信号被阻塞，直到旧信号被处理完成。再发送该信号的时候只能记录一个，其余的被丢弃掉。



在执行信号处理函数的时候，使用的是临时阻塞的信号集，处理完后使用内核中的阻塞信号集。



当一个信号被阻塞的时候，再发送该信号的时候只能记录一个，其余的被丢弃掉（只有一个标记位），不支持排队。



下面介绍`SIGCHLD`信号。



`SIGCHLD`信号产生的条件:

1. 子进程终止时（最常用）；

2. 子进程接收到`SIGSTOP`信号停止时；

3. 子进程处在停止态，接受到`SIGCONT`后唤醒时；

以上三种条件内核都会给父进程发送`SIGCHLD`信号，父进程默认会忽略该信号。



但是`SIGCHLD`可以解决僵尸进程，在父进程捕捉该信号，在使用`wait`进行回收，其余时刻由父进程进行自己工作。



```c
/*
    SIGCHLD信号产生的3个条件：
        1.子进程结束
        2.子进程暂停了
        3.子进程继续运行
        都会给父进程发送该信号，父进程默认忽略该信号。
    
    使用SIGCHLD信号解决僵尸进程的问题。
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/wait.h>

void myFun(int num) {
    printf("捕捉到的信号 ：%d\n", num);
    // 回收子进程PCB的资源
    // while(1) {
    //     wait(NULL); 
    // }
    while(1) {
       int ret = waitpid(-1, NULL, WNOHANG);
       if(ret > 0) {
           printf("child die , pid = %d\n", ret);
       } else if(ret == 0) {
           // 说明还有子进程或者
           break;
       } else if(ret == -1) {
           // 没有子进程
           break;
       }
    }
}

int main() {

    // 提前设置好阻塞信号集，阻塞SIGCHLD，因为有可能子进程很快结束，父进程还没有注册完信号捕捉
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGCHLD);
    sigprocmask(SIG_BLOCK, &set, NULL);

    // 创建一些子进程
    pid_t pid;
    for(int i = 0; i < 20; i++) {
        pid = fork();
        if(pid == 0) {
            break;
        }
    }

    if(pid > 0) {
        // 父进程

        // 捕捉子进程死亡时发送的SIGCHLD信号
        struct sigaction act;
        act.sa_flags = 0;
        act.sa_handler = myFun;
        sigemptyset(&act.sa_mask);
        sigaction(SIGCHLD, &act, NULL);

        // 注册完信号捕捉以后，解除阻塞
        sigprocmask(SIG_UNBLOCK, &set, NULL);

        while(1) {
            printf("parent process pid : %d\n", getpid());
            sleep(2);
        }
    } else if( pid == 0) {
        // 子进程
        printf("child process pid : %d\n", getpid());
    }

    return 0;
}
```

### 共享内存

共享内存允许两个或者多个进程共享物理内存的同一块区域（通常被称为段)。由于一个共享内存段会成为一个进程用户空间的一部分，因此这种IPC机制无需内核介入（相比于其他进程，内核介入次数少）。所有需要做的就是让一个进程将数据复制进共享内存中，并且这部分数据会对其他所有共享同一个段的进程可用。



与管道等要求发送进程将数据从用户空间的缓冲区复制进内核内存和接收进程将数据从内核内存复制进用户空间的缓冲区的做法相比，这种IPC技术的速度更快。



1. 调用 `shmget() `创建一个新共享内存段或取得一个既有共享内存段的标识符（即由其他进程创建的共享内存段）。这个调用将返回后续调用中需要用到的共享内存标识符。
2. 使用 `shmat() `来附上共享内存段，即使该段成为调用进程的虚拟内存的一部分。
3.  此刻在程序中可以像对待其他可用内存那样对待这个共享内存段。为引用这块共享内存，程序需要使用由 `shmat()` 调用返回的 addr 值，它是一个指向进程的虚拟地址空间中该共享内存段的起点的指针。
4. 调用 `shmdt()` 来分离共享内存段。在这个调用之后，进程就无法再引用这块共享内存了。这一步是可选的，并且在进程终止时会自动完成这一步。
5. 调用 `shmctl()` 来删除共享内存段。只有当当前所有附加内存段的进程都与之分离之后内存段才会销毁。只有一个进程需要执行这一步。

```c
共享内存相关的函数
#include <sys/ipc.h>
#include <sys/shm.h>

int shmget(key_t key, size_t size, int shmflg);
    - 功能：创建一个新的共享内存段，或者获取一个既有的共享内存段的标识。
        新创建的内存段中的数据都会被初始化为0
    - 参数：
        - key : key_t类型是一个整形，通过这个找到或者创建一个共享内存。
                一般使用16进制表示，非0值
        - size: 共享内存的大小,以最小分页大小来进行分配
        - shmflg: 属性
            - 访问权限
            - 附加属性：创建/判断共享内存是不是存在
                - 创建：IPC_CREAT
                - 判断共享内存是否存在： IPC_EXCL , 需要和IPC_CREAT一起使用
                    IPC_CREAT | IPC_EXCL | 0664
        - 返回值：
            失败：-1 并设置错误号
            成功：>0 返回共享内存的引用的ID，后面操作共享内存都是通过这个值。


void *shmat(int shmid, const void *shmaddr, int shmflg);
    - 功能：和当前的进程进行关联
    - 参数：
        - shmid : 共享内存的标识（ID）,由shmget返回值获取
        - shmaddr: 申请的共享内存的起始地址，指定NULL，内核指定
        - shmflg : 对共享内存的操作
            - 读 ： SHM_RDONLY, 必须要有读权限
            - 读写： 0
    - 返回值：
        成功：返回共享内存的首（起始）地址。  失败(void *) -1


int shmdt(const void *shmaddr);
    - 功能：解除当前进程和共享内存的关联
    - 参数：
        shmaddr：共享内存的首地址
    - 返回值：成功 0， 失败 -1

int shmctl(int shmid, int cmd, struct shmid_ds *buf);
    - 功能：对共享内存进行操作。删除共享内存，共享内存要删除才会消失，创建共享内存的进行被销毁了对共享内存是没有任何影响。
    - 参数：
        - shmid: 共享内存的ID
        - cmd : 要做的操作
            - IPC_STAT : 获取共享内存的当前的状态
            - IPC_SET : 设置共享内存的状态
            - IPC_RMID: 标记共享内存被销毁
        - buf：需要设置或者获取的共享内存的属性信息
            - IPC_STAT : buf存储数据
            - IPC_SET : buf中需要初始化数据，设置到内核中
            - IPC_RMID : 没有用，NULL

key_t ftok(const char *pathname, int proj_id);
    - 功能：根据指定的路径名，和int值，生成一个共享内存的key
    - 参数：
        - pathname:指定一个存在的路径
            /home/nowcoder/Linux/a.txt
            / 
        - proj_id: int类型的值，但是这系统调用只会使用其中的1个字节
                   范围 ： 0-255  一般指定一个字符 'a'


问题1：操作系统如何知道一块共享内存被多少个进程关联？
    - 共享内存维护了一个结构体struct shmid_ds 这个结构体中有一个成员 shm_nattch
    - shm_nattach 记录了关联的进程个数

问题2：可不可以对共享内存进行多次删除 shmctl
    - 可以的
    - 因为shmctl 标记删除共享内存，不是直接删除
    - 什么时候真正删除呢?
        当和共享内存关联的进程数为0的时候，就真正被删除
    - 当共享内存的key为0的时候，表示共享内存被标记删除了
        如果一个进程和共享内存取消关联，那么这个进程就不能继续操作这个共享内存。也不能进行关联。

    共享内存和内存映射的区别
    1.共享内存可以直接创建，内存映射需要磁盘文件（匿名映射除外）
    2.共享内存效果更高
    3.内存
        所有的进程操作的是同一块共享内存。
        内存映射，每个进程在自己的虚拟地址空间中有一个独立的内存。
    4.数据安全
        - 进程突然退出
            共享内存还存在
            内存映射区消失
        - 运行进程的电脑死机，宕机了
            数据存在在共享内存中，没有了
            内存映射区的数据 ，由于磁盘文件中的数据还在，所以内存映射区的数据还存在。

    5.生命周期
        - 内存映射区：进程退出，内存映射区销毁
        - 共享内存：进程退出，共享内存还在，标记删除（所有的关联的进程数为0），或者关机
            如果一个进程退出，会自动和共享内存进行取消关联。
```

```c
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main() {    

    // 1.获取一个共享内存
    int shmid = shmget(100, 0, IPC_CREAT);
    printf("shmid : %d\n", shmid);

    // 2.和当前进程进行关联
    void * ptr = shmat(shmid, NULL, 0);

    // 3.读数据
    printf("%s\n", (char *)ptr);
    
    printf("按任意键继续\n");
    getchar();

    // 4.解除关联
    shmdt(ptr);

    // 5.删除共享内存
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
```

```c
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main() {    

    // 1.创建一个共享内存
    int shmid = shmget(100, 4096, IPC_CREAT|0664);
    printf("shmid : %d\n", shmid);
    
    // 2.和当前进程进行关联
    void * ptr = shmat(shmid, NULL, 0);

    char * str = "helloworld";

    // 3.写数据
    memcpy(ptr, str, strlen(str) + 1);

    printf("按任意键继续\n");
    getchar();

    // 4.解除关联
    shmdt(ptr);

    // 5.删除共享内存
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
```

# Linux多线程开发



与进程(process）类似．线程(thread)是允许应用程序并发执行多个任务的一种机制。一个进程可以包含多个线程。同一个程序中的所有线程均会独立执行相同程序，且共享同一份全局内存区域，其中包括初始化数据段、未初始化数据段，以及堆内存段。(传统意义上的 UNIX进程只是多线程程序的一个特例，该进程只包含一个线程)



进程是 CPU分配资源的最小单位，线程是操作系统调度执行的最小单位。



线程是轻量级的进程(LWP: Light weight Process) ，在Linux环境下线程的本质仍是进程。查看指定进程的 LWP 号: `ps -Lf pid`


线程和进程的区别：

1. 进程间的信息难以共享。由于除去只读代码段外，父子进程并未共享内存，因此必须采用一些进程间通信方式，在进程间进行信息交换。
2. 调用fork ()来创建进程的代价相对较高，即便利用写时复制技术．仍热需要复制诸如内存页表和文件描述符表之类的多种进程属性，这意味着fork()调用在时间上的开销依然不菲。
3. 线程之间能够方便、快速地共享信息。只霜将数据复制到共享（全局或堆）变量中即可。创建线程比创建进程通常要快10 倍甚至更多。线程间是共享虚拟地址空间的无需采用写时复制来复制内存，也无需复制页表。

`.text`段、栈空间都会分为各个线程的栈



线程的共享和非共享资源：



共享资源（内核数据）：

1. 进程ID 和父进程ID
2. 进程组ID和会话ID
3. 用户ID和用户组ID
4. 文件描述符表
5. 信号处置
6. 文件系统的相关信息:文件权限掩码栈，本地变量和函数的调用链接信息
   (umask)、当前工作目录
7. 虚拟地址空间(除栈、`.text`)

非共享资源:

1. 线程ID
2. 信号掩码
3. 线程特有数据
4. error变量
5. 实时调度策略和优先级
6. 栈、本地变量和函数的调用链接信息



当 Linux 最初开发时，在内核中并不能真正支持线程。但是它的确可以通过 `clone()` 系统调用将进程作为可调度的实体。这个调用创建了调用进程（calling process）的一个拷贝，这个拷贝与调用进程共享相同的地址空间。LinuxThreads 项目使用这个调用来完成在用户空间模拟对线程的支持。不幸的是，这种方法有一些缺点，尤其是在信号处理、调度和进程间同步等方面都存在问题。另外，这个线程模型也不符合 POSIX 的要求。



要改进 LinuxThreads，需要内核的支持，并且重写线程库。有两个相互竞争的项目开始来满足这些要求。一个包括 IBM 的开发人员的团队开展了 NGPT（Next-Generation POSIX Threads）项目。同时，Red Hat 的一些开发人员开展了 NPTL 项目。NGPT 在 2003 年中期被放弃了，把这个领域完全留给了 NPTL。



NPTL，或称为 Native POSIX Thread Library，是 Linux 线程的一个新实现，它克服了 LinuxThreads 的缺点，同时也符合 POSIX 的需求。与 LinuxThreads 相

比，它在性能和稳定性方面都提供了重大的改进。



查看当前 `pthread` 库版本：`getconf GNU_LIBPTHREAD_VERSION`



有时，一个线程需要同时访问两个或更多不同的共享资源，而每个资源又都由不同的互斥量管理。当超过一个线程加锁同一组互斥量时，就有可能发生死锁。



两个或两个以上的进程在执行过程中，因争夺共享资源而造成的一种互相等待的现象，若无外力作用，它们都将无法推进下去。此时称系统处于死锁状态或系统产生了死锁。



死锁的几种场景：

- 忘记释放锁

- 重复加锁（两个都尝试看对面想不想锁，发现对方没有，自己上锁）

- 多线程多锁，抢占锁资源

  

![image-20240328222133008](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240328222133008.png)



## 线程相关函数

常见的线程函数：

1. int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *( *start_routine) (void *), void *arg);

2. pthread_t pthread_self(void);

3. int pthread_equal(pthread_t t1, pthread_t t2);

4. void pthread_exit(void *retval);

5. int pthread_join(pthread_t thread, void **retval);

6. int pthread_detach(pthread_t thread);

7. int pthread_cancel(pthread_t thread);

   

线程属性类型 `pthread_attr_t`

1. int pthread_attr_init(pthread_attr_t *attr);
2. int pthread_attr_destroy(pthread_attr_t *attr);
3. int pthread_attr_getdetachstate(const pthread_attr_t *attr, int *detachstate);
13.  int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate);

### `create`函数

```c
/*
    一般情况下,main函数所在的线程我们称之为主线程（main线程），其余创建的线程
    称之为子线程。
    程序中默认只有一个进程，fork()函数调用，2进程
    程序中默认只有一个线程，pthread_create()函数调用，2个线程。

    #include <pthread.h>
    int pthread_create(pthread_t *thread, const pthread_attr_t *attr, 
    void *(*start_routine) (void *), void *arg);

        - 功能：创建一个子线程
        - 参数：
            - thread：传出参数，线程创建成功后，子线程的线程ID被写到该变量中
            - attr : 设置线程的属性，一般使用默认值，NULL
            - start_routine : 函数指针，这个函数是子线程需要处理的逻辑代码
            - arg : 给第三个参数使用，传参，但是是void*类型（单个参数），多个参数传递的时候需要进行结构体设计，把信息保存到再传入
        - 返回值：
            成功：0
            失败：返回错误号。这个错误号和之前errno不太一样。
            获取错误号的信息：  char * strerror(int errnum);

*/
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

void * callback(void * arg) { //子线程执行代码
    printf("child thread...\n");
    printf("arg value: %d\n", *(int *)arg);
    return NULL;
}

int main() {

    pthread_t tid;

    int num = 10;

    // 创建一个子线程
    int ret = pthread_create(&tid, NULL, callback, (void *)&num);

    if(ret != 0) {
        char * errstr = strerror(ret);
        printf("error : %s\n", errstr);
    } 

    for(int i = 0; i < 5; i++) {
        printf("%d\n", i);
    }

    sleep(1);//主线程执行完销毁子线程没抢到CPU，子线程无法进行，所有这里需要睡一下

    return 0;   // exit(0);
}
```

### `exit`/`self`/`equal`函数

```c++
/*

    #include <pthread.h>
    void pthread_exit(void *retval);
        功能：终止一个线程，在哪个线程中调用，就表示终止哪个线程
        参数：
            retval:需要传递一个指针，作为一个返回值，可以在pthread_join()中获取到。

    pthread_t pthread_self(void);
        功能：获取当前的线程的线程ID

    int pthread_equal(pthread_t t1, pthread_t t2);
        功能：比较两个线程ID是否相等
        不同的操作系统，pthread_t类型的实现不一样，有的是无符号的长整型，有的
        是使用结构体去实现的。
*/
#include <stdio.h>
#include <pthread.h>
#include <string.h>

void * callback(void * arg) {
    printf("child thread id : %ld\n", pthread_self());
    return NULL;    // pthread_exit(NULL);
} 

int main() {

    // 创建一个子线程
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, callback, NULL);

    if(ret != 0) {
        char * errstr = strerror(ret);
        printf("error : %s\n", errstr);
    }

    // 主线程
    for(int i = 0; i < 5; i++) {
        printf("%d\n", i);
    }

    printf("tid : %ld, main thread id : %ld\n", tid ,pthread_self());

    // 让主线程退出,当主线程退出时，不会影响其他正常运行的线程，即转换到就绪态。
    pthread_exit(NULL);

    printf("main thread exit\n");

    return 0;   // exit(0);
}
```

不同于进程，进程回收由父进程和`INIT`进程回收，而线程可以回收任意子进程。

### `join`函数

```c
/*
    #include <pthread.h>
    int pthread_join(pthread_t thread, void **retval);
        - 功能：和一个已经终止的线程进行连接
                回收子线程的资源
                这个函数是阻塞函数，调用一次只能回收一个子线程
                一般在主线程中使用
        - 参数：
            - thread：需要回收的子线程的ID
            - retval: 接收子线程退出时的返回值
        - 返回值：
            0 : 成功
            非0 : 失败，返回的错误号
*/

#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

int value = 10;

void * callback(void * arg) {
    printf("child thread id : %ld\n", pthread_self());
    // sleep(3);
    // return NULL; 
    // int value = 10; // 局部变量返回无效，因为子线程结束以后栈也会被释放，这里选择返回全局变量
    pthread_exit((void *)&value);   // return (void *)&value;
} 

int main() {

    // 创建一个子线程
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, callback, NULL);

    if(ret != 0) {
        char * errstr = strerror(ret);
        printf("error : %s\n", errstr);
    }

    // 主线程
    for(int i = 0; i < 5; i++) {
        printf("%d\n", i);
    }

    printf("tid : %ld, main thread id : %ld\n", tid ,pthread_self());

    // 主线程调用pthread_join()回收子线程的资源
    int * thread_retval;
    ret = pthread_join(tid, (void **)&thread_retval); //注意是二级指针，因为返回是一级指针，想操作必须传递二级指针

    if(ret != 0) {
        char * errstr = strerror(ret);
        printf("error : %s\n", errstr);
    }

    printf("exit data : %d\n", *thread_retval);

    printf("回收子线程资源成功！\n");

    // 让主线程退出,当主线程退出时，不会影响其他正常运行的线程。
    pthread_exit(NULL);

    return 0; 
}

```

### `detach`函数

```c
/*
    #include <pthread.h>
    int pthread_detach(pthread_t thread);
        - 功能：分离一个线程。被分离的线程在终止的时候，会自动释放资源返回给系统。
          1.不能多次分离，会产生不可预料的行为。
          2.不能去连接一个已经分离的线程，会报错。
        - 参数：需要分离的线程的ID
        - 返回值：
            成功：0
            失败：返回错误号
*/
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

void * callback(void * arg) {
    printf("chid thread id : %ld\n", pthread_self());
    return NULL;
}

int main() {

    // 创建一个子线程
    pthread_t tid;

    int ret = pthread_create(&tid, NULL, callback, NULL);
    if(ret != 0) {
        char * errstr = strerror(ret);
        printf("error1 : %s\n", errstr);
    }

    // 输出主线程和子线程的id
    printf("tid : %ld, main thread id : %ld\n", tid, pthread_self());

    // 设置子线程分离,子线程分离后，子线程结束时对应的资源就不需要主线程释放
    ret = pthread_detach(tid);
    if(ret != 0) {
        char * errstr = strerror(ret);
        printf("error2 : %s\n", errstr);
    }

    // 设置分离后，对分离的子线程进行连接 pthread_join()
    // ret = pthread_join(tid, NULL);
    // if(ret != 0) {
    //     char * errstr = strerror(ret);
    //     printf("error3 : %s\n", errstr);
    // }

    pthread_exit(NULL);

    return 0;
}
```

### `cancel`函数

```c
/*
    #include <pthread.h>
    int pthread_cancel(pthread_t thread);
        - 功能：取消线程（让线程终止）
            取消某个线程，可以终止某个线程的运行，
            但是并不是立马终止，而是当子线程执行到一个取消点，线程才会终止,如果子线程中没有取消点的话，子线程一直运行到结束。
            取消点：系统规定好的一些系统调用，我们可以粗略的理解为从用户区到内核区的切换，这个位置称之为取消点。
*/

#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

void * callback(void * arg) {
    printf("chid thread id : %ld\n", pthread_self());
    for(int i = 0; i < 5; i++) {
        printf("child : %d\n", i);
    }
    return NULL;
}

int main() {
    
    // 创建一个子线程
    pthread_t tid;

    int ret = pthread_create(&tid, NULL, callback, NULL);
    if(ret != 0) {
        char * errstr = strerror(ret);
        printf("error1 : %s\n", errstr);
    }

    // 取消线程
    pthread_cancel(tid);

    for(int i = 0; i < 5; i++) {
        printf("%d\n", i);
    }

    // 输出主线程和子线程的id
    printf("tid : %ld, main thread id : %ld\n", tid, pthread_self());

    
    pthread_exit(NULL);

    return 0;
}
```

### `init`/`destroy`/`getdetachstate`/`setdetachstate`函数

```c
/*
    int pthread_attr_init(pthread_attr_t *attr);
        - 初始化线程属性变量

    int pthread_attr_destroy(pthread_attr_t *attr);
        - 释放线程属性的资源

    int pthread_attr_getdetachstate(const pthread_attr_t *attr, int *detachstate);
        - 获取线程分离的状态属性

    int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate);
        - 设置线程分离的状态属性
*/     

#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

void * callback(void * arg) {
    printf("chid thread id : %ld\n", pthread_self());
    return NULL;
}

int main() {

    // 创建一个线程属性变量
    pthread_attr_t attr;
    // 初始化属性变量
    pthread_attr_init(&attr);

    // 设置属性
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    // 创建一个子线程
    pthread_t tid;

    int ret = pthread_create(&tid, &attr, callback, NULL);
    if(ret != 0) {
        char * errstr = strerror(ret);
        printf("error1 : %s\n", errstr);
    }

    // 获取线程的栈的大小(有默认值)
    size_t size;
    pthread_attr_getstacksize(&attr, &size);
    printf("thread stack size : %ld\n", size);

    // 输出主线程和子线程的id
    printf("tid : %ld, main thread id : %ld\n", tid, pthread_self());

    // 释放线程属性资源
    pthread_attr_destroy(&attr);

    pthread_exit(NULL);

    return 0;
}
```

## 线程同步



线程的主要优势在于，能够通过全局变量来共享信息。不过，这种便捷的共享是有代价的：必须确保多个线程不会同时修改同一变量，或者某一线程不会读取正在由其他线程修改的变量。



临界区是指访问某一共享资源的代码片段，并且这段代码的执行应为原子操作，也就是同时访问同一共享资源的其他线程不应终端该片段的执行。



线程同步：即当有一个线程在对内存进行操作时，其他线程都不可以对这个内存地址进行操作，直到该线程完成操作，其他线程才能对该内存地址进行操作，而其他线程则处于等待状态。



```c
/*
    使用多线程实现买票的案例。
    有3个窗口，一共是100张票。
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// 全局变量，所有的线程都共享这一份资源。
int tickets = 100;

void * sellticket(void * arg) {
    // 卖票
    while(tickets > 0) {
        usleep(6000);//睡眠多少微秒，因为cpu执行的非常快，这里usleep就是让当前的线程休眠，这样好让出cpu。主要是为了演示效果
        printf("%ld 正在卖第 %d 张门票\n", pthread_self(), tickets);
        tickets--;
    }
    return NULL;
}

int main() {

    // 创建3个子线程
    pthread_t tid1, tid2, tid3;
    pthread_create(&tid1, NULL, sellticket, NULL);
    pthread_create(&tid2, NULL, sellticket, NULL);
    pthread_create(&tid3, NULL, sellticket, NULL);

    // 回收子线程的资源,阻塞
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);

    // 设置线程分离。
    // pthread_detach(tid1);
    // pthread_detach(tid2);
    // pthread_detach(tid3);

    pthread_exit(NULL); // 退出主线程

    return 0;
}
```

### 互斥锁（互斥）

为避免线程更新共享变量时出现问题，可以使用互斥量（mutex 是 mutual exclusion的缩写）来确保同时仅有一个线程可以访问某项共享资源。可以使用互斥量来保证对任意共享资源的原子访问。



互斥量有两种状态：已锁定（locked）和未锁定（unlocked）。任何时候，至多只有一个线程可以锁定该互斥量。试图对已经锁定的某一互斥量再次加锁，将可能阻塞线程或者报错失败，具体取决于加锁时使用的方法。



一旦线程锁定互斥量，随即成为该互斥量的所有者，只有所有者才能给互斥量解锁。一般情况下，对每一共享资源（可能由多个相关变量组成）会使用不同的互斥量，每一线程在访问同一资源时将采用如下协议：

- 针对共享资源锁定互斥量
- 访问共享资源
- 对互斥量解锁

如果多个线程试图执行这一块代码（一个临界区），事实上只有一个线程能够持有该互斥量（其他线程将遭到阻塞），即同时只有一个线程能够进入这段代码区域，如下图所示：



![image-20240328221248093](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240328221248093.png)

互斥量函数：

1. 互斥量的类型 `pthread_mutex_t`

2. int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);

3. int pthread_mutex_destroy(pthread_mutex_t *mutex);

4. int pthread_mutex_lock(pthread_mutex_t *mutex);
5.  int pthread_mutex_trylock(pthread_mutex_t *mutex);
6. int pthread_mutex_unlock(pthread_mutex_t *mutex);

```c
/*
    互斥量的类型 pthread_mutex_t
    int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);
        - 初始化互斥量
        - 参数 ：
            - mutex ： 需要初始化的互斥量变量
            - attr ： 互斥量相关的属性，NULL
        - restrict : C语言的修饰符，被修饰的指针，不能由另外的一个指针进行操作。
            pthread_mutex_t *restrict mutex = xxx;
            pthread_mutex_t * mutex1 = mutex;

    int pthread_mutex_destroy(pthread_mutex_t *mutex);
        - 释放互斥量的资源

    int pthread_mutex_lock(pthread_mutex_t *mutex);
        - 加锁，阻塞的，如果有一个线程加锁了，那么其他的线程只能阻塞等待

    int pthread_mutex_trylock(pthread_mutex_t *mutex);
        - 尝试加锁，如果加锁失败，不会阻塞，会直接返回。

    int pthread_mutex_unlock(pthread_mutex_t *mutex);
        - 解锁
*/
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// 全局变量，所有的线程都共享这一份资源。
int tickets = 1000;

// 创建一个互斥量
pthread_mutex_t mutex;

void * sellticket(void * arg) {

    // 卖票，408
    while(1) {

        // 加锁，下面是临界区
        pthread_mutex_lock(&mutex);

        if(tickets > 0) {
            usleep(6000);
            printf("%ld 正在卖第 %d 张门票\n", pthread_self(), tickets);
            tickets--;
        }else {
            // 解锁
            pthread_mutex_unlock(&mutex);
            break;
        }

        // 解锁
        pthread_mutex_unlock(&mutex);
    }

    

    return NULL;
}

int main() {

    // 初始化互斥量
    pthread_mutex_init(&mutex, NULL);

    // 创建3个子线程
    pthread_t tid1, tid2, tid3;
    pthread_create(&tid1, NULL, sellticket, NULL);
    pthread_create(&tid2, NULL, sellticket, NULL);
    pthread_create(&tid3, NULL, sellticket, NULL);

    // 回收子线程的资源,阻塞
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);

    pthread_exit(NULL); // 退出主线程

    // 释放互斥量资源
    pthread_mutex_destroy(&mutex);

    return 0;
}
```





### 读写锁（同步）

当有一个线程已经持有互斥锁时，互斥锁将所有试图进入临界区的线程都阻塞住。但是考虑一种情形，当前持有互斥锁的线程只是要读访问共享资源，而同时有其它几个线程也想读取这个共享资源，但是由于互斥锁的排它性，所有其它线程都无法获取锁，也就无法读访问共享资源了，但是实际上多个线程同时读访问共享资源并不会导致问题。



在对数据的读写操作中，更多的是读操作，写操作较少，例如对数据库数据的读写应用。为了满足当前能够允许多个读出，但只允许一个写入的需求，线程提供了读写锁来实现。



读写锁的特点：

1. 如果有其它线程读数据，则允许其它线程执行读操作，但不允许写操作。
2. 如果有其它线程写数据，则其它线程都不允许读、写操作。
3. 写是独占的，写的优先级高。



读写锁函数：基本函数：



1. 读写锁的类型 pthread_rwlock_t，
2. int pthread_rwlock_init(pthread_rwlock_t *restrict rwlock, const pthread_rwlockattr_t *restrict attr);
3. int pthread_rwlock_destroy(pthread_rwlock_t *rwlock);
4. int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);
5. int pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock);
6. int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);
7. int pthread_rwlock_trywrlock(pthread_rwlock_t *rwlock);
8. int pthread_rwlock_unlock(pthread_rwlock_t *rwlock);



```c
/*
    读写锁的类型 pthread_rwlock_t
    int pthread_rwlock_init(pthread_rwlock_t *restrict rwlock, const pthread_rwlockattr_t *restrict attr);
    int pthread_rwlock_destroy(pthread_rwlock_t *rwlock);
    int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);
    int pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock);
    int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);
    int pthread_rwlock_trywrlock(pthread_rwlock_t *rwlock);
    int pthread_rwlock_unlock(pthread_rwlock_t *rwlock);

    案例：8个线程操作同一个全局变量。
    3个线程不定时写这个全局变量，5个线程不定时的读这个全局变量
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// 创建一个共享数据
int num = 1;
// pthread_mutex_t mutex;
pthread_rwlock_t rwlock;

void * writeNum(void * arg) {

    while(1) {
        //上锁
        pthread_rwlock_wrlock(&rwlock);
        num++;
        printf("++write, tid : %ld, num : %d\n", pthread_self(), num);
        pthread_rwlock_unlock(&rwlock);//解锁
        usleep(100);
    }

    return NULL;
}

void * readNum(void * arg) {

    while(1) {
        pthread_rwlock_rdlock(&rwlock);
        printf("===read, tid : %ld, num : %d\n", pthread_self(), num);
        pthread_rwlock_unlock(&rwlock);
        usleep(100);
    }

    return NULL;
}

int main() {

   pthread_rwlock_init(&rwlock, NULL);

    // 创建3个写线程，5个读线程
    pthread_t wtids[3], rtids[5];
    for(int i = 0; i < 3; i++) {
        pthread_create(&wtids[i], NULL, writeNum, NULL);
    }

    for(int i = 0; i < 5; i++) {
        pthread_create(&rtids[i], NULL, readNum, NULL);
    }

    // 设置线程分离
    for(int i = 0; i < 3; i++) {
       pthread_detach(wtids[i]);
    }

    for(int i = 0; i < 5; i++) {
         pthread_detach(rtids[i]);
    }

    pthread_exit(NULL);

    pthread_rwlock_destroy(&rwlock);

    return 0;
}
```

### 生产者消费者模型

生产者生产东西，放入缓冲区，消费者从缓冲区中拿，缓冲区互斥。



放入前先判断容器有无满，拿出前判断容器是否空，即PV操作（信号量）。也可以用局部变量解决。



```c
/*
    生产者消费者模型（粗略的版本）
*/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

// 创建一个互斥量
pthread_mutex_t mutex;

struct Node{
    int num;
    struct Node *next;
};

// 头结点
struct Node * head = NULL;

void * producer(void * arg) {

    // 不断的创建新的节点，添加到链表中
    while(1) {
        pthread_mutex_lock(&mutex);
        struct Node * newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->next = head;
        head = newNode;
        newNode->num = rand() % 1000; //随机数赋值
        printf("add node, num : %d, tid : %ld\n", newNode->num, pthread_self());
        pthread_mutex_unlock(&mutex);
        usleep(100);
    }

    return NULL;
}

void * customer(void * arg) {

    while(1) { //假如一直没用数据，customer一直循环判断有没有数据，浪费系统性能
        pthread_mutex_lock(&mutex);
        // 保存头结点的指针
        struct Node * tmp = head;
        // 判断是否有数据，否则会导致野指针问题，head->next=null
        if(head != NULL) {
            // 有数据
            head = head->next;
            printf("del node, num : %d, tid : %ld\n", tmp->num, pthread_self());
            free(tmp);
            pthread_mutex_unlock(&mutex);
            usleep(100);
        } else {
            // 没有数据，也要释放锁，否则导致死锁问题
            pthread_mutex_unlock(&mutex);
        }
    }
    return  NULL;
}

int main() {

    pthread_mutex_init(&mutex, NULL);

    // 创建5个生产者线程，和5个消费者线程
    pthread_t ptids[5], ctids[5];

    for(int i = 0; i < 5; i++) {
        pthread_create(&ptids[i], NULL, producer, NULL);
        pthread_create(&ctids[i], NULL, customer, NULL);
    }

    for(int i = 0; i < 5; i++) {
        pthread_detach(ptids[i]);
        pthread_detach(ctids[i]);
    }

    while(1) { //执行detach后不应该直接把互斥量销毁，所以加上循环
        sleep(10);
    }

    pthread_mutex_destroy(&mutex);

    pthread_exit(NULL);

    return 0;
}
```

### 条件变量

为了避免customer一直循环判断有没有数据，浪费系统性能，引入一个新的思路：当缓冲区内部没有数据的时候，请求生产者来进行生产，直到生产了以后消费者继续执行。



条件变量不是锁，而是关键在于某个条件下进行解除阻塞/阻塞，保存数据不混乱必须使用互斥量。



条件变量的类型 `pthread_cond_t`，基本函数：

1.  int pthread_cond_init(pthread_cond_t *restrict cond, const pthread_condattr_t *restrict attr);
2. int pthread_cond_destroy(pthread_cond_t *cond);
3. int pthread_cond_wait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex);
4. int pthread_cond_timedwait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex, const struct timespec *restrict abstime);
5. int pthread_cond_signal(pthread_cond_t *cond);
6. int pthread_cond_broadcast(pthread_cond_t *cond);

```c
/*
    条件变量的类型 pthread_cond_t
    int pthread_cond_init(pthread_cond_t *restrict cond, const pthread_condattr_t *restrict attr);
    int pthread_cond_destroy(pthread_cond_t *cond);
    int pthread_cond_wait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex);
        - 等待，调用了该函数，线程会阻塞。
    int pthread_cond_timedwait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex, const struct timespec *restrict abstime);
        - 等待多长时间，调用了这个函数，线程会阻塞，直到指定的时间结束。
    int pthread_cond_signal(pthread_cond_t *cond);
        - 唤醒一个或者多个等待的线程
    int pthread_cond_broadcast(pthread_cond_t *cond);
        - 唤醒所有的等待的线程
*/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

// 创建一个互斥量
pthread_mutex_t mutex;
// 创建条件变量
pthread_cond_t cond;

struct Node{
    int num;
    struct Node *next;
};

// 头结点
struct Node * head = NULL;

void * producer(void * arg) {

    // 不断的创建新的节点，添加到链表中
    while(1) {
        pthread_mutex_lock(&mutex);
        struct Node * newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->next = head;
        head = newNode;
        newNode->num = rand() % 1000;
        printf("add node, num : %d, tid : %ld\n", newNode->num, pthread_self());
        
        // 只要生产了一个，就通知消费者消费
        pthread_cond_signal(&cond);

        pthread_mutex_unlock(&mutex);
        usleep(100);
    }

    return NULL;
}

void * customer(void * arg) {

    while(1) {
        pthread_mutex_lock(&mutex);
        // 保存头结点的指针
        struct Node * tmp = head;
        // 判断是否有数据
        if(head != NULL) {
            // 有数据
            head = head->next;
            printf("del node, num : %d, tid : %ld\n", tmp->num, pthread_self());
            free(tmp);
            pthread_mutex_unlock(&mutex);
            usleep(100);
        } else {
            // 没有数据，需要等待
            // 当这个函数调用阻塞的时候，会对互斥锁进行解锁，当不阻塞的，继续向下执行，会重新加锁。
            pthread_cond_wait(&cond, &mutex);
            pthread_mutex_unlock(&mutex);
        }
    }
    return  NULL;
}

int main() {

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    // 创建5个生产者线程，和5个消费者线程
    pthread_t ptids[5], ctids[5];

    for(int i = 0; i < 5; i++) {
        pthread_create(&ptids[i], NULL, producer, NULL);
        pthread_create(&ctids[i], NULL, customer, NULL);
    }

    for(int i = 0; i < 5; i++) {
        pthread_detach(ptids[i]);
        pthread_detach(ctids[i]);
    }

    while(1) {
        sleep(10);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    pthread_exit(NULL);

    return 0;
}
```

### 信号量

信号量（信号灯），是不保证多线程数据的安全问题，保证安全问题需要和互斥锁一切使用。记录值为可用资源数。



信号量的类型`sem_t`，基本函数：

1. int sem_init(sem_t *sem, int pshared, unsigned int value);
2. int sem_destroy(sem_t *sem);
3. int sem_wait(sem_t *sem);
4. int sem_trywait(sem_t *sem);
5. int sem_timedwait(sem_t *sem, const struct timespec *abs_timeout);
6. int sem_post(sem_t *sem);
7. int sem_getvalue(sem_t *sem, int *sval);

在信号量的基础上，条件变量就不需要了，也不需要进行判断了。

```c
/*
    信号量的类型 sem_t
    int sem_init(sem_t *sem, int pshared, unsigned int value);
        - 初始化信号量
        - 参数：
            - sem : 信号量变量的地址
            - pshared : 0 用在线程间 ，非0 用在进程间
            - value : 信号量中的值

    int sem_destroy(sem_t *sem);
        - 释放资源

    int sem_wait(sem_t *sem);
        - 对信号量加锁，调用一次对信号量的值-1，如果值为0，就阻塞

    int sem_trywait(sem_t *sem);

    int sem_timedwait(sem_t *sem, const struct timespec *abs_timeout);
    int sem_post(sem_t *sem);
        - 对信号量解锁，调用一次对信号量的值+1

    int sem_getvalue(sem_t *sem, int *sval);

    sem_t psem;
    sem_t csem;
    init(psem, 0, 8);
    init(csem, 0, 0);

    producer() {
        sem_wait(&psem);
        sem_post(&csem)
    }

    customer() {
        sem_wait(&csem);
        sem_post(&psem)
    }

*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

// 创建一个互斥量
pthread_mutex_t mutex;
// 创建两个信号量
sem_t psem;
sem_t csem;

struct Node{
    int num;
    struct Node *next;
};

// 头结点
struct Node * head = NULL;

void * producer(void * arg) {

    // 不断的创建新的节点，添加到链表中
    while(1) {
        sem_wait(&psem);
        pthread_mutex_lock(&mutex);
        struct Node * newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->next = head;
        head = newNode;
        newNode->num = rand() % 1000;
        printf("add node, num : %d, tid : %ld\n", newNode->num, pthread_self());
        pthread_mutex_unlock(&mutex);
        sem_post(&csem);
    }

    return NULL;
}

void * customer(void * arg) {

    while(1) {
        sem_wait(&csem);
        pthread_mutex_lock(&mutex);
        // 保存头结点的指针
        struct Node * tmp = head;
        head = head->next;
        printf("del node, num : %d, tid : %ld\n", tmp->num, pthread_self());
        free(tmp);
        pthread_mutex_unlock(&mutex);
        sem_post(&psem);
       
    }
    return  NULL;
}

int main() {

    pthread_mutex_init(&mutex, NULL);
    sem_init(&psem, 0, 8);
    sem_init(&csem, 0, 0);

    // 创建5个生产者线程，和5个消费者线程
    pthread_t ptids[5], ctids[5];

    for(int i = 0; i < 5; i++) {
        pthread_create(&ptids[i], NULL, producer, NULL);
        pthread_create(&ctids[i], NULL, customer, NULL);
    }

    for(int i = 0; i < 5; i++) {
        pthread_detach(ptids[i]);
        pthread_detach(ctids[i]);
    }

    while(1) {
        sleep(10);
    }

    pthread_mutex_destroy(&mutex);

    pthread_exit(NULL);

    return 0;
}

```

大端小端的定义。

```c
/*  
    字节序：字节在内存中存储的顺序。
    小端字节序：数据的高位字节存储在内存的高位地址，低位字节存储在内存的低位地址
    大端字节序：数据的低位字节存储在内存的高位地址，高位字节存储在内存的低位地址
*/

// 通过代码检测当前主机的字节序
#include <stdio.h>

int main() {

    union {
        short value;    // 2字节
        char bytes[sizeof(short)];  // char[2]
    } test;

    test.value = 0x0102;
    if((test.bytes[0] == 1) && (test.bytes[1] == 2)) {
        printf("大端字节序\n");
    } else if((test.bytes[0] == 2) && (test.bytes[1] == 1)) {
        printf("小端字节序\n");
    } else {
        printf("未知\n");
    }

    return 0;
}
```

# Linux网络编程

## 网络结构模式

### C/S结构

服务器 - 客户机，即 Client - Server（C/S）结构。C/S 结构通常采取两层结构。服务器负责数据的管理，客户机负责完成与用户的交互任务。客户机是因特网上访问别人信息的机器，服务器则是提供信息供人访问的计算机。



客户机通过局域网与服务器相连，接受用户的请求，并通过网络向服务器提出请求，对数据库进行操作。服务器接受客户机的请求，将数据提交给客户机，客户机将数据进行计算并将结果呈现给用户。服务器还要提供完善安全保护及对数据完整性的处理等操作，并允许多个客户机同时访问服务器，这就对服务器的硬件处理数据能力提出了很高的要求。



在C/S结构中，应用程序分为两部分：服务器部分和客户机部分。服务器部分是多个用户共享的信息与功能，执行后台服务，如控制共享数据库的操作等；客户机部分为用户所专有，负责执行前台功能，在出错提示、在线帮助等方面都有强大的功能，并且可以在子程序间自由切换。



C/S结构优点：

1. 能充分发挥客户端 PC 的处理能力，很多工作可以在客户端处理后再提交给服务器，所以 C/S 结构客户端响应速度快；

2. 操作界面漂亮、形式多样，可以充分满足客户自身的个性化要求；
3. C/S 结构的管理信息系统具有较强的事务处理能力，能实现复杂的业务流程；
4. 安全性较高，C/S 一般面向相对固定的用户群，程序更加注重流程，它可以对权限进行多层次校验，提供了更安全的存取模式，对信息安全的控制能力很强，一般高度机密的信息系统采用 C/S 结构适宜。

C/S结构缺点：

1. 客户端需要安装专用的客户端软件。首先涉及到安装的工作量，其次任何一台电脑出问题，如病毒、硬件损坏，都需要进行安装或维护。系统软件升级时，每一台客户机需要重新安装，其维护和升级成本非常高；

2. 对客户端的操作系统一般也会有限制，不能够跨平台。



### B/S结构

B/S 结构（Browser/Server，浏览器/服务器模式），是 WEB 兴起后的一种网络结构模式，WEB浏览器是客户端最主要的应用软件。这种模式统一了客户端，将系统功能实现的核心部分集中到服务器上，简化了系统的开发、维护和使用。客户机上只要安装一个浏览器，如 Firefox 或 Internet Explorer，服务器安装 SQL Server、Oracle、MySQL 等数据库。浏览器通过 Web Server 同数据库进行数据交互。



B/S结构优点：

1. B/S 架构最大的优点是总体拥有成本低、维护方便、 分布性强、开发简单。
2. 可以不用安装任何专门的软件就能实现在任何地方进行操作客户端零维护，系统的扩展非常容易，只要有一台能上网的电脑就能使用。



B/S结构缺点：

1. 通信开销大、系统和数据的安全性较难保障；
2. 个性特点明显降低，无法实现具有个性化的功能要求；
3. 协议一般是固定的：`http`/`https`；
4. 客户端服务器端的交互是请求-响应模式，通常动态刷新页面，响应速度明显降低；



## MAC地址

网卡是一块被设计用来允许计算机在计算机网络上进行通讯的计算机硬件，又称为网络适配器或网络接口卡NIC。其拥有 MAC 地址，属于 OSI 模型的第 2 层，它使得用户可以通过电缆或无线相互连接。每一个网卡都有一个被称为 MAC 地址的独一无二的 48 位串行号。



网卡的主要功能：

1. 数据的封装与解封装；
2. 链路管理；
3. 数据编码与译码；



MAC 地址（Media Access Control Address），直译为媒体存取控制位址，也称为局域网地址、以太网地址、物理地址或硬件地址，它是一个用来确认网络设备位置的位址，由网络设备制造商生产时烧录在网卡中。在 OSI 模型中，第三层网络层负责 IP 地址，第二层数据链路层则负责 MAC位址 。MAC 地址用于在网络中唯一标识一个网卡，一台设备若有一或多个网卡，则每个网卡都需要并会有一个唯一的 MAC 地址。



MAC 地址的长度为 48 位（6个字节），通常表示为 12 个 16 进制数，如：00-16-EA-AE-3C-40 就是一个MAC 地址，其中前 3 个字节，16 进制数 00-16-EA 代表网络硬件制造商的编号，它由IEEE（电气与电子工程师协会）分配，而后 3 个字节，16进制数 AE-3C-40 代表该制造商所制造的某个网络产品（如网卡）的系列号。只要不更改自己的 MAC 地址，MAC 地址在世界是唯一的。形象地说，MAC 地址就如同身份证上的身份证号码，具有唯一性。



## IP地址



IP 协议是为计算机网络相互连接进行通信而设计的协议。在因特网中，它是能使连接到网上的所有计算机网络实现相互通信的一套规则，规定了计算机在因特网上进行通信时应当遵守的规则。任何厂家生产的计算机系统，只要遵守 IP 协议就可以与因特网互连互通。



各个厂家生产的网络系统和设备，如以太网、分组交换网等，它们相互之间不能互通，不能互通的主要原因是因为它们所传送数据的基本单元（技术上称之为“帧”）的格式不同。IP 协议实际上是一套由软件程序组成的协议软件，它把各种不同“帧”统一转换成“IP 数据报”格式，这种转换是因特网的一个最重要的特点，使所有各种计算机都能在因特网上实现互通，即具有“开放性”的特点。正是因为有了 IP 协议，因特网才得以迅速发展成为世界上最大的、开放的计算机通信网络。因此，IP 协议也可以叫做“因特网协议”。



IP 地址（Internet Protocol Address）是指互联网协议地址，又译为网际协议地址。IP 地址是 IP协议提供的一种统一的地址格式，它为互联网上的每一个网络和每一台主机分配一个逻辑地址，以此来屏蔽物理地址的差异。



IP 地址是一个 32 位的二进制数，通常被分割为 4 个“ 8 位二进制数”（也就是 4 个字节）。IP 地址通常用“点分十进制”表示成（a.b.c.d）的形式，其中，a,b,c,d都是 0~255 之间的十进制整数。例：点分十进IP地址（100.4.5.6），实际上是 32 位二进制数（01100100.00000100.00000101.00000110）。



最初设计互联网络时，为了便于寻址以及层次化构造网络，每个 IP 地址包括两个标识码（ID），即网络ID 和主机 ID。同一个物理网络上的所有主机都使用同一个网络 ID，网络上的一个主机（包括网络上工作站，服务器和路由器等）有一个主机 ID 与其对应。Internet 委员会定义了 5 种 IP 地址类型以适合不

同容量的网络，即 A 类~ E 类。其中 A、B、C 3类（如下表格）由 Internet NIC 在全球范围内统一分配，D、E 类为特殊地址。

## 子网掩码

子网掩码（subnet mask）又叫网络掩码、地址掩码、子网络遮罩，它是一种用来指明一个 IP 地址的哪些位标识的是主机所在的子网，以及哪些位标识的是主机的位掩码。子网掩码不能单独存在，它必须结合 IP 地址一起使用。子网掩码只有一个作用，就是将某个 IP 地址划分成网络地址和

主机地址两部分。



子网掩码是一个 32 位地址，用于屏蔽 IP 地址的一部分以区别网络标识和主机标识，并说明该 IP地址是在局域网上，还是在广域网上。

## 端口

“端口” 是英文 port 的意译，可以认为是设备与外界通讯交流的出口。端口可分为虚拟端口和物理端口，其中虚拟端口指计算机内部或交换机路由器内的端口，不可见，是特指TCP/IP协议中的端口，是逻辑意义上的端口。例如计算机中的 80 端口、21 端口、23 端口等。物理端口又称为接口，是可见端口，计算机背板的 RJ45 网口，交换机路由器集线器等 RJ45 端口。电话使用 RJ11 插口也属于物理端口的范畴。



如果把 IP 地址比作一间房子，端口就是出入这间房子的门。真正的房子只有几个门，但是一个 IP地址的端口可以有 65536（即：2^16）个之多！端口是通过端口号来标记的，端口号只有整数，范围是从 0 到65535（2^16-1）。

## 网络模型

### OSI 七层模型

七层模型，亦称 OSI（Open System Interconnection）参考模型，即开放式系统互联。参考模型是国际标准化组织（ISO）制定的一个用于计算机或通信系统间互联的标准体系，一般称为 OSI 参考模型或七层模型。它是一个七层的、抽象的模型体，不仅包括一系列抽象的术语或概念，也包括具体的协议。



OSI 七层参考模型分为：

1. 物理层：主要定义物理设备标准，如网线的接口类型、光纤的接口类型、各种传输介质的传输速率等。它的主要作用是传输比特流（就是由1、0转化为电流强弱来进行传输，到达目的地后再转化为1、0，也就是我们常说的数模转换与模数转换）。这一层的数据叫做比特。
2. 数据链路层：建立逻辑连接、进行硬件地址寻址、差错校验等功能。定义了如何让格式化数据以帧为单位进行传输，以及如何让控制对物理介质的访问。将比特组合成字节进而组合成帧，用MAC地址访问介质。
3. 网络层：进行逻辑地址寻址，在位于不同地理位置的网络中的两个主机系统之间提供连接和路径选择。Internet的发展使得从世界各站点访问信息的用户数大大增加，而网络层正是管理这种连接的层。
4. 传输层：定义了一些传输数据的协议和端口号（ WWW 端口 80 等），如：TCP（传输控制协议，传输效率低，可靠性强，用于传输可靠性要求高，数据量大的数据），UDP（用户数据报协议，与TCP 特性恰恰相反，用于传输可靠性要求不高，数据量小的数据，如 QQ 聊天数据就是通过这种方式传输的）。 主要是将从下层接收的数据进行分段和传输，到达目的地址后再进行重组。常常把这一层数据叫做段。
5. 会话层：通过传输层（端口号：传输端口与接收端口）建立数据传输的通路。主要在你的系统之间发起会话或者接受会话请求。
6. 表示层：数据的表示、安全、压缩。主要是进行对接收的数据进行解释、加密与解密、压缩与解压缩等（也就是把计算机能够识别的东西转换成人能够能识别的东西（如图片、声音等）。
7. 应用层：网络服务与最终用户的一个接口。这一层为用户的应用程序（例如电子邮件、文件传输和终端仿真）提供网络服务。

### TCP/IP 四层模型

TCP/IP 协议在一定程度上参考了 OSI 的体系结构。OSI 模型共有七层，从下到上分别是物理层、数据链路层、网络层、传输层、会话层、表示层和应用层。但是这显然是有些复杂的，所以在 TCP/IP 协议中，它们被简化为了四个层次。

1. 应用层、表示层、会话层三个层次提供的服务相差不是很大，所以在 TCP/IP 协议中，它们被合并为应用层一个层次。
2. 由于传输层和网络层在网络协议中的地位十分重要，所以在 TCP/IP 协议中它们被作为独立的两个层次。
3. 因为数据链路层和物理层的内容相差不多，所以在 TCP/IP 协议中它们被归并在网络接口层一个层次里。只有四层体系结构的 TCP/IP 协议，与有七层体系结构的 OSI 相比要简单了不少，也正是这样，TCP/IP 协议在实际的应用中效率更高，成本更低。



TCP/IP 四层模型分为：

1. 应用层：应用层是 TCP/IP 协议的第一层，是直接为应用进程提供服务的。

   - 对不同种类的应用程序它们会根据自己的需要来使用应用层的不同协议，邮件传输应用使用了 SMTP 协议、万维网应用使用了 HTTP 协议、远程登录服务应用使用了有 TELNET 协议。

   - 应用层还能加密、解密、格式化数据。

   - 应用层可以建立或解除与其他节点的联系，这样可以充分节省网络资源。

2. 传输层：作为 TCP/IP 协议的第二层，运输层在整个 TCP/IP 协议中起到了中流砥柱的作用。且在运输层中， TCP 和 UDP 也同样起到了中流砥柱的作用。

3. 网络层：网络层在 TCP/IP 协议中的位于第三层。在 TCP/IP 协议中网络层可以进行网络连接的建立和终止以及 IP 地址的寻找等功能。

4. 网络接口层：在 TCP/IP 协议中，网络接口层位于第四层。由于网络接口层兼并了物理层和数据链路层所以，网络接口层既是传输数据的物理媒介，也可以为网络层提供一条准确无误的线路。

## 协议

协议，网络协议的简称，网络协议是通信计算机双方必须共同遵从的一组约定。如怎么样建立连接、怎么样互相识别等。只有遵守这个约定，计算机之间才能相互通信交流。它的三要素是：语法、语义、时序。



为了使数据在网络上从源到达目的，网络通信的参与方必须遵循相同的规则，这套规则称为协议（protocol），它最终体现为在网络上传输的数据包的格式。

协议往往分成几个层次进行定义，分层定义是为了使某一层协议的改变不影响其他层次的协议。



常见协议如下：

1. 应用层常见的协议有：FTP协议、HTTP协议）、NFS；
2. 传输层常见协议有：TCP协议、UDP协议；
3. 网络层常见协议有：IP 协议、ICMP 协议、IGMP 协议；
4. 网络接口层常见协议有：ARP协议、RARP协议；

## 封装与分用

上层协议是如何使用下层协议提供的服务的呢？其实这是通过封装（encapsulation）实现的。应用程序数据在发送到物理网络上之前，将沿着协议栈从上往下依次传递。每层协议都将在上层数据的基础上加上自己的头部信息（有时还包括尾部信息），以实现该层的功能，这个过程就称为封装。



当帧到达目的主机时，将沿着协议栈自底向上依次传递。各层协议依次处理帧中本层负责的头部数据，以获取所需的信息，并最终将处理后的帧交给目标应用程序。这个过程称为分用（demultiplexing）。分用是依靠头部信息中的类型字段实现的。

## socket

所谓 socket（套接字），就是对网络中不同主机上的应用进程之间进行双向通信的端点的抽象。一个套接字就是网络上进程通信的一端，提供了应用层进程利用网络协议交换数据的机制。从所处的地位来讲，套接字上联应用进程，下联网络协议栈，是应用程序通过网络协议进行通信的接口，

是应用程序与网络协议根进行交互的接口。



socket 可以看成是两个网络应用程序进行通信时，各自通信连接中的端点，这是一个逻辑上的概念。它是网络环境中进程间通信的 API，也是可以被命名和寻址的通信端点，使用中的每一个套接字都有其类型和一个与之相连进程。通信时其中一个网络应用程序将要传输的一段信息写入它所在主机的 socket 中，该 socket 通过与网络接口卡（NIC）相连的传输介质将这段信息送到另外一台主机的 socket 中，使对方能够接收到这段信息。socket 是由 IP 地址和端口结合的，提供向应用

层进程传送数据包的机制。



socket 本身有“插座”的意思，在 Linux 环境下，用于表示进程间网络通信的特殊文件类型。本质为内核借助缓冲区形成的伪文件。既然是文件，那么理所当然的，我们可以使用文件描述符引用套接字。与管道类似的，Linux 系统将其封装成文件的目的是为了统一接口，使得读写套接字和读写文件的操作一致。区别是管道主要应用于本地进程间通信，而套接字多应用于网络进程间数据的传递。



套接字通信分两部分：

1. 服务器端：被动接受连接，一般不会主动发起连接；
2. 客户端：主动向服务器发起连接；



socket是一套通信的接口，Linux 和 Windows 都有，但是有一些细微的差别。



### 字节序



现代 CPU 的累加器一次都能装载（至少）4 字节（这里考虑 32 位机），即一个整数。那么这 4字节在内存中排列的顺序将影响它被累加器装载成的整数的值，这就是字节序问题。在各种计算机体系结构中，对于字节、字等的存储机制有所不同，因而引发了计算机通信领域中一个很重要的问题，即通信双方交流的信息单元（比特、字节、字、双字等等）应该以什么样的顺序进行传送。如果不达成一致的规则，通信双方将无法进行正确的编码/译码从而导致通信失败。



字节序，顾名思义字节的顺序，就是大于一个字节类型的数据在内存中的存放顺序（一个字节的数据当然就无需谈顺序的问题了）。



字节序分为大端字节序（Big-Endian） 和小端字节序（Little-Endian）。



大端字节序是指一个整数的最高位字节（23 ~ 31 bit）存储在内存的低地址处，低位字节（0 ~ 7 bit）存储在内存的高地址处；小端字节序则是指整数的高位字节存储在内存的高地址处，而低位字节则存储在内存的低地址处。



### 字节序转换函数

当格式化的数据在两台使用不同字节序的主机之间直接传递时，接收端必然错误的解释之。解决问题的方法是：发送端总是把要发送的数据转换成大端字节序数据后再发送，而接收端知道对方传送过来的数据总是采用大端字节序，所以接收端可以根据自身采用的字节序决定是否对接收到的数据进行转换（小端机转换，大端机不转换）。



网络字节顺序是 TCP/IP 中规定好的一种数据表示格式，它与具体的 CPU 类型、操作系统等无关，从而可以保证数据在不同主机之间传输时能够被正确解释，网络字节顺序采用大端排序方式。BSD Socket提供了封装好的转换接口，方便程序员使用。包括从主机字节序到网络字节序的转换函数：`htons`、`htonl`；从网络字节序到主机字节序的转换函数：`ntohs`、`ntohl`。（参数`s` 代表- short unsigned short，参数`l`代表 - long unsigned int）



```c
#include <arpa/inet.h>
// 转换端口
uint16_t htons(uint16_t hostshort); // 主机字节序 - 网络字节序
uint16_t ntohs(uint16_t netshort); // 主机字节序 - 网络字节序
// 转IP
uint32_t htonl(uint32_t hostlong); // 主机字节序 - 网络字节序
uint32_t ntohl(uint32_t netlong); // 主机字节序 - 网络字节序

typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef uint16_t in_port_t;
typedef uint32_t in_addr_t;
```

socket地址其实是一个结构体，封装端口号和IP等信息。后面的socket相关的`api`中需要使用到这个socket地址。

```c
/*

    网络通信时，需要将主机字节序转换成网络字节序（大端），
    另外一段获取到数据以后根据情况将网络字节序转换成主机字节序。

    // 转换端口
    uint16_t htons(uint16_t hostshort);		// 主机字节序 - 网络字节序
    uint16_t ntohs(uint16_t netshort);		// 主机字节序 - 网络字节序

    // 转IP
    uint32_t htonl(uint32_t hostlong);		// 主机字节序 - 网络字节序
    uint32_t ntohl(uint32_t netlong);		// 主机字节序 - 网络字节序

*/

#include <stdio.h>
#include <arpa/inet.h>

int main() {

    // htons 转换端口
    unsigned short a = 0x0102;
    printf("a : %x\n", a);
    unsigned short b = htons(a);
    printf("b : %x\n", b);

    printf("=======================\n");

    // htonl  转换IP
    char buf[4] = {192, 168, 1, 100};//初始化char数组类型，但是在C++中是不存在隐式转换
    int num = *(int *)buf;//转化成int*buf，再*取值，即得到一个整数1921681100
    int sum = htonl(num);//又因为int和long的字节大小相同，仍然是四个字节
    unsigned char *p = (char *)&sum; //取地址且把数据转换为char*,此时又变为一个字节一个字节的形式

    printf("%d %d %d %d\n", *p, *(p+1), *(p+2), *(p+3));

    printf("=======================\n");

    // ntohl
    unsigned char buf1[4] = {1, 1, 168, 192};
    int num1 = *(int *)buf1;
    int sum1 = ntohl(num1);
    unsigned char *p1 = (unsigned char *)&sum1;
    printf("%d %d %d %d\n", *p1, *(p1+1), *(p1+2), *(p1+3));

    // ntohs


    return 0;
}
```

### 判断当前系统的字节序

```c
// 通过代码检测当前主机的字节序
#include <stdio.h>

int main() {

    union {
        short value;    // short大小为2字节
        char bytes[sizeof(short)];  // sizeof(short)大小为2，char[2]大小为两个字节
    } test;

    test.value = 0x0102; //赋值为十六进制的数字，为两个字节01，02
    if((test.bytes[0] == 1) && (test.bytes[1] == 2)) {
        printf("大端字节序\n");
    } else if((test.bytes[0] == 2) && (test.bytes[1] == 1)) {
        printf("小端字节序\n");
    } else {
        printf("未知\n");
    }

    return 0;
}
```

### 通用socket地址

socket 网络编程接口中表示 socket 地址的是结构体 `sockaddr`，其定义如下：

```c
#include <bits/socket.h>

struct sockaddr {
sa_family_t sa_family;
char sa_data[14];
};

typedef unsigned short int sa_family_t;
```

`sa_family`成员是地址族类型（`sa_family_t`）的变量。地址族类型通常与协议族类型对应。常见的协议族（protocol family，也称 domain）和对应的地址族入下所示：

| **协议族** | **地址族** | **描述**         |
| ---------- | ---------- | ---------------- |
| PF_UNIX    | AF_UNIX    | UNIX本地域协议族 |
| PF_INET    | AF_INET    | TCP/IPv4协议族   |
| PF_INET6   | AF_INET6   | TCP/IPv6协议族   |

宏 PF_* 和 AF_* 都定义在 `bits/socket.h` 头文件中，且后者与前者有完全相同的值，所以二者通常混用。`sa_data`成员用于存放 socket 地址值。但是，不同的协议族的地址值具有不同的含义和长度，如下所示：

| **协议族** | 地址值含义和长度                                             |
| ---------- | ------------------------------------------------------------ |
| PF_UNIX    | 文件的路径名，长度可达到108字节                              |
| PF_INET    | 16 bit 端口号和 32 bit IPv4 地址，共 6 字节                  |
| PF_INET6   | 16 bit 端口号，32 bit 流标识，128 bit IPv6 地址，32 bit 范围 ID，共 26 字节 |

由上表可知，14 字节的`sa_data`根本无法容纳多数协议族的地址值。因此`Linux`定义了下面这个新的通用的`socket`地址结构体，这个结构体不仅提供了足够大的空间用于存放地址值，而且是内存对齐的。

```c
#include <bits/socket.h>
struct sockaddr_storage
{
sa_family_t sa_family;
unsigned long int __ss_align;
char __ss_padding[ 128 - sizeof(__ss_align) ];
};
typedef unsigned short int sa_family_t;
```

但是在实际开发的过程中我们很少使用通用的socket地址。

### 专用socket地址

很多网络编程函数诞生早于 IPv4 协议，那时候都使用的是`struct sockaddr`结构体，为了向前兼容，现在`sockaddr`退化成了（`void *`）的作用，传递一个地址给函数，至于这个函数是`sockaddr_in`还是`sockaddr_in6`，由地址族确定，然后函数内部再强制类型转化为所需的地址类型。



即我们使用的是是`sockaddr_in`，在为了向前兼容，最后都会进行强制转换。



UNIX 本地域协议族使用如下专用的 socket 地址结构体：

```c
#include <sys/un.h>
struct sockaddr_un
{
    sa_family_t sin_family;
    char sun_path[108];
};
```

TCP/IP 协议族有 `sockaddr_in` （开发常用）和 `sockaddr_in6` 两个专用的 socket 地址结构体，它们分别用于 IPv4 和IPv6：

```c
#include <netinet/in.h>
struct sockaddr_in
{
    sa_family_t sin_family; /* __SOCKADDR_COMMON(sin_) */
    in_port_t sin_port; /* Port number. */
    struct in_addr sin_addr; /* Internet address. */
    /* Pad to size of `struct sockaddr'. */
    unsigned char sin_zero[sizeof (struct sockaddr) - __SOCKADDR_COMMON_SIZE -
                           sizeof (in_port_t) - sizeof (struct in_addr)];
};
struct in_addr
{
    in_addr_t s_addr;
};
struct sockaddr_in6
{
    sa_family_t sin6_family;
    in_port_t sin6_port; /* Transport layer port # */
    uint32_t sin6_flowinfo; /* IPv6 flow information */
    struct in6_addr sin6_addr; /* IPv6 address */
    uint32_t sin6_scope_id; /* IPv6 scope-id */
};

typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef uint16_t in_port_t;
typedef uint32_t in_addr_t;
#define __SOCKADDR_COMMON_SIZE (sizeof (unsigned short int))
```

所有专用`socket`地址（以及`sockaddr_storage`）类型的变量在实际使用时都需要转化为通用 `socket` 地址类型 `sockaddr`（强制转化即可），因为所有 `socket` 编程接口使用的地址参数类型都是 `sockaddr`。

### socket函数

```c
#include <arpa/inet.h> 

int socket(int domain, int type, int protocol);
    - 功能：创建一个套接字
    - 参数：
    - domain: 协议族
        AF_INET : ipv4
        AF_INET6 : ipv6
        AF_UNIX, AF_LOCAL : 本地套接字通信（进程间通信）
	- type: 通信过程中使用的协议类型
        SOCK_STREAM : 流式协议(对应TCP面向字节流)
        SOCK_DGRAM : 报式协议(对应UDP面向报文)
    - protocol : 具体的一个协议。一般写0
        - SOCK_STREAM : 流式协议默认使用 TCP
        - SOCK_DGRAM : 报式协议默认使用 UDP
    - 返回值：
    - 成功：返回文件描述符，操作的就是内核缓冲区。
    - 失败：-1
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen); // socket命名
    - 功能：绑定，将fd 和本地的IP + 端口进行绑定
    - 参数：
        - sockfd : 通过socket函数得到的文件描述符
        - addr : 需要绑定的socket地址，这个地址封装了ip和端口号的信息
        - addrlen : 第二个参数结构体占的内存大小
int listen(int sockfd, int backlog); // /proc/sys/net/core/somaxconn
    - 功能：监听这个socket上的连接
    - 参数：
        - sockfd : 通过socket()函数得到的文件描述符
        - backlog : 未连接的和已经连接的和的最大值， 5
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
    - 功能：接收客户端连接，默认是一个阻塞的函数，阻塞等待客户端连接
    - 参数：
        - sockfd : 用于监听的文件描述符
        - addr : 传出参数，记录了连接成功后客户端的地址信息（ip，port）
        - addrlen : 指定第二个参数的对应的内存大小
    - 返回值：
        - 成功 ：用于通信的文件描述符
        - -1 ： 失败
int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    - 功能： 客户端连接服务器
    - 参数：
        - sockfd : 用于通信的文件描述符
        - addr : 客户端要连接的服务器的地址信息
        - addrlen : 第二个参数的内存大小
    - 返回值：成功 0， 失败 -1
      ssize_t write(int fd, const void *buf, size_t count); // 写数据
      ssize_t read(int fd, void *buf, size_t count); // 读数据
```

## IP地址转换

通常，人们习惯用可读性好的字符串来表示 IP 地址，比如用点分十进制字符串表示 IPv4 地址，以及用十六进制字符串表示 IPv6 地址。但编程中我们需要先把它们转化为整数（二进制数）方能使用。而记录日志时则相反，我们要把整数表示的 IP 地址转化为可读的字符串。下面 3 个函数可用于用点分十进制字符串表示的 IPv4 地址和用网络字节序整数表示的 IPv4 地址之间的转换。

```c
#include <arpa/inet.h>
in_addr_t inet_addr(const char *cp);
int inet_aton(const char *cp, struct in_addr *inp);
char *inet_ntoa(struct in_addr in);
```

下面这对更新的函数也能完成前面 3 个函数同样的功能，并且它们同时适用 IPv4 地址和 IPv6 地址：

```c
#include <arpa/inet.h>

// p:点分十进制的IP字符串，n:表示network，网络字节序的整数
int inet_pton(int af, const char *src, void *dst);
af:地址族： AF_INET AF_INET6
src:需要转换的点分十进制的IP字符串
dst:转换后的结果保存在这个里面
   
// 将网络字节序的整数，转换成点分十进制的IP地址字符串
const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);
af:地址族： AF_INET AF_INET6
src: 要转换的ip的整数的地址
dst: 转换成IP地址字符串保存的地方
size：第三个参数的大小（数组的大小）
返回值：返回转换后的数据的地址（字符串），和 dst 是一样的
```

```c
/*
    #include <arpa/inet.h>
    // p:点分十进制的IP字符串，n:表示network，网络字节序的整数
    int inet_pton(int af, const char *src, void *dst);
        af:地址族： AF_INET  AF_INET6
        src:需要转换的点分十进制的IP字符串
        dst:转换后的结果保存在这个里面

    // 将网络字节序的整数，转换成点分十进制的IP地址字符串
    const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);
        af:地址族： AF_INET  AF_INET6
        src: 要转换的ip的整数的地址
        dst: 转换成IP地址字符串保存的地方
        size：第三个参数的大小（数组的大小）
        返回值：返回转换后的数据的地址（字符串），和 dst 是一样的

*/

#include <stdio.h>
#include <arpa/inet.h>

int main() {

    // 创建一个ip字符串,点分十进制的IP地址字符串
    char buf[] = "192.168.1.4";
    unsigned int num = 0;

    // 将点分十进制的IP字符串转换成网络字节序的整数
    inet_pton(AF_INET, buf, &num);
    unsigned char * p = (unsigned char *)&num;
    printf("%d %d %d %d\n", *p, *(p+1), *(p+2), *(p+3));


    // 将网络字节序的IP整数转换成点分十进制的IP字符串
    char ip[16] = ""; //十进制每个位为3位，则一共12位，加上字符串结束符和`.`，一共16位
    const char * str =  inet_ntop(AF_INET, &num, ip, 16);
    printf("str : %s\n", str);
    printf("ip : %s\n", str);
    printf("%d\n", ip == str);

    return 0;
}
```



## `TCP`通信

服务器端 （被动接受连接的角色）：

1. `socket`创建一个用于监听有客户端的连接的套接字（文件描述符）`serverfd`；
   
2. 设置服务器`socket`地址，设置对应的`sin_family`模式，服务器的IP、端口绑定。将这个监听文件描述符`serverfd`和服务器`socket`进行绑定；
   
3. 设置监听`listen`，设置最大连接数，`serverfd`开始工作；
4. 设置客户端`socket`地址准备接收客户端`socket`地址，调用`accept`阻塞等待，当有客户端发起连接，解除阻塞，接受客户端的连接，把客户端的信息存入客户端`socket`地址，返回客户端通信套接字`clientfd`；

5. 通信，接收数据和发送数据，读写数据是利用`clientfd`进行；

6. 通信结束，断开连接，关闭`serverfd`和`clientfd`；



客户端：

1. `socket`创建一个用于连接服务端的连接的套接字（文件描述符）`serverfd`；
2. 设置服务器`socket`地址，设置对应的`sin_family`模式，服务器的IP、端口绑定。将这个监听文件描述符`serverfd`和服务器`socket`进行绑定；
3. `connect`连接服务器，需要指定连接的服务器的 IP 和 端口；
4. 连接成功了，客户端可以直接和服务器通信，接收数据和发送数据，读写数据是利用`serverfd`进行；

5. 通信结束，断开连接,关闭`serverfd`；



由计算机网络通信可知，客户端和服务端通信需要以`socket`地址进行通信。客户端建立`serverfd`并绑定服务器对应信息是为了连接客户端进行通信。服务器建立`serverfd`并绑定服务器对应信息是为了监听客户端。

```c
// TCP 通信的服务器端

#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main() {

    // 1.创建socket(用于监听的套接字)
    int lfd = socket(AF_INET, SOCK_STREAM, 0);

    if(lfd == -1) {
        perror("socket");
        exit(-1);
    }

    // 2.绑定
    struct sockaddr_in saddr; //一般情况下使用sockaddr_in类中，最后进行指针转换向前兼容
    //设置sockaddr_in参数
    //struct sockaddr_in
    //{
    //   sa_family_t sin_family; /* __SOCKADDR_COMMON(sin_) */
    //   in_port_t sin_port; /* Port number. */
    //  struct in_addr sin_addr; /* Internet address. */
    	/* Pad to size of `struct sockaddr'. */
    //   unsigned char sin_zero[sizeof (struct sockaddr) - __SOCKADDR_COMMON_SIZE -
    //                         sizeof (in_port_t) - sizeof (struct in_addr)];
    //};
    saddr.sin_family = AF_INET;
    // inet_pton(AF_INET, "192.168.193.128", saddr.sin_addr.s_addr); //可以把点分十进制的IP字符串转换为整数
    saddr.sin_addr.s_addr = INADDR_ANY;  // IP地址，整数，INADDR_ANY是宏值，代表任意地址0.0.0.0(代表本主机，防止多网卡多IP)
    saddr.sin_port = htons(9999); //端口号，整数，但是这里直接赋值是会主机字节序
    int ret = bind(lfd, (struct sockaddr *)&saddr, sizeof(saddr));

    if(ret == -1) {
        perror("bind");
        exit(-1);
    }

    // 3.监听
    ret = listen(lfd, 8);
    if(ret == -1) {
        perror("listen");
        exit(-1);
    }

    // 4.接收客户端连接
    //accept函数参数列表的socket地址是连接进来的客户端的信息，因此重新定义sockaddr_in
    struct sockaddr_in clientaddr;
    int len = sizeof(clientaddr);
    int cfd = accept(lfd, (struct sockaddr *)&clientaddr, &len); 
    if(cfd == -1) {
        perror("accept");
        exit(-1);
    }

    // 输出客户端的信息
    char clientIP[16];
    inet_ntop(AF_INET, &clientaddr.sin_addr.s_addr, clientIP, sizeof(clientIP));//IP地址转换，记录IP地址
    unsigned short clientPort = ntohs(clientaddr.sin_port);//记录端口号
    printf("client ip is %s, port is %d\n", clientIP, clientPort);

    // 5.通信
    char recvBuf[1024] = {0};
    while(1) { //让其一直收到数据读取数据
        
        // 获取客户端的数据
        int num = read(cfd, recvBuf, sizeof(recvBuf)); //socket网络编程是抽象成文件的，使用read(fd,char*,len)
        if(num == -1) {
            perror("read");
            exit(-1);
        } else if(num > 0) {
            printf("recv client data : %s\n", recvBuf);
        } else if(num == 0) { 
            // 表示客户端断开连接
            printf("clinet closed...");
            break;
        }

        const char * data = "hello,i am server";
        // 给客户端发送数据
        write(cfd, data, strlen(data)); //写数据同样是read形式
    }
   
    // 关闭文件描述符
    close(cfd);
    close(lfd);

    return 0;
}
```

```c
// TCP通信的客户端

#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main() {

    // 1.创建套接字
    int fd = socket(AF_INET, SOCK_STREAM, 0);//IP4,
    if(fd == -1) {
        perror("socket");
        exit(-1);
    }

    // 2.连接服务器端
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    inet_pton(AF_INET, "192.168.193.128", &serveraddr.sin_addr.s_addr);
    serveraddr.sin_port = htons(9999);
    int ret = connect(fd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

    if(ret == -1) {
        perror("connect");
        exit(-1);
    }

    
    // 3. 通信
    char recvBuf[1024] = {0};
    while(1) {

        char * data = "hello,i am client";
        // 给客户端发送数据
        write(fd, data , strlen(data));

        sleep(1);
        
        int len = read(fd, recvBuf, sizeof(recvBuf));
        if(len == -1) {
            perror("read");
            exit(-1);
        } else if(len > 0) {
            printf("recv server data : %s\n", recvBuf);
        } else if(len == 0) {
            // 表示服务器端断开连接
            printf("server closed...");
            break;
        }

    }

    // 关闭连接
    close(fd);

    return 0;
}
```

请实现回射服务器（发送数据给服务器端，服务器把这些数据再返回给客户端）、在客户端接收键盘录入的数据，服务器端再回复消息。



经典的连接和断开流程和滑动窗口机制、状态转换请参考相关笔记。

## 并发服务器的开发

在上面的`.c`程序中，只能支持一个客户端连接，`accept`只执行一次，因此无法进行。服务器如果想要处理并发任务，必须以多线程或者多进程进行开发。

### 多进程实现

使用一个主进程进行连接，把通信交给子进程执行，每链接一个客户端则生产一个子进程，为单主进程多子进程的模式。

```c
// TCP通信的服务端
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <wait.h>
#include <errno.h>

void recyleChild(int arg) {
    while(1) { //当是多个子进程发送的时候需要把资源回收，因此需要循环处理所有子进程结束后的资源
        int ret = waitpid(-1, NULL, WNOHANG);
        if(ret == -1) {
            // 所有的子进程都回收了
            break;
        }else if(ret == 0) {
            // 还有子进程活着
            break;
        } else if(ret > 0){
            // 被回收了
            printf("子进程 %d 被回收了\n", ret);
        }
    }
}

int main() {

    struct sigaction act;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    act.sa_handler = recyleChild;
    // 注册信号捕捉
    sigaction(SIGCHLD, &act, NULL);
    

    // 创建socket
    int lfd = socket(PF_INET, SOCK_STREAM, 0);
    if(lfd == -1){
        perror("socket");
        exit(-1);
    }

    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(9999);
    saddr.sin_addr.s_addr = INADDR_ANY;

    // 绑定
    int ret = bind(lfd,(struct sockaddr *)&saddr, sizeof(saddr));
    if(ret == -1) {
        perror("bind");
        exit(-1);
    }

    // 监听
    ret = listen(lfd, 128);
    if(ret == -1) {
        perror("listen");
        exit(-1);
    }

    // 不断循环等待客户端连接
    while(1) {
		//不能在这里回收，`wait`阻塞和`waitpid`阻塞不能进来，非阻塞也不太好
        struct sockaddr_in cliaddr;
        int len = sizeof(cliaddr);
        // 接受连接,没有客户端连接的时候为阻塞，当系统调用因为信号（回收进程回调函数）被软中断会产生EINTR错误
        int cfd = accept(lfd, (struct sockaddr*)&cliaddr, &len);
        if(cfd == -1) {
            if(errno == EINTR) { //这个错误记录在errno里面，软中断错误继续执行
                continue;
            }
            perror("accept"); //accept本身错误
            exit(-1);
        }

        // 每一个连接进来，创建一个子进程跟客户端通信
        pid_t pid = fork();
        if(pid == 0) {
            // pid=0，子进程
            // 获取客户端的信息
            char cliIp[16];
            inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr, cliIp, sizeof(cliIp));
            unsigned short cliPort = ntohs(cliaddr.sin_port);
            printf("client ip is : %s, prot is %d\n", cliIp, cliPort);

            // 接收客户端发来的数据
            char recvBuf[1024];
            while(1) {
                int len = read(cfd, &recvBuf, sizeof(recvBuf));

                if(len == -1) {
                    perror("read");
                    exit(-1);
                }else if(len > 0) {
                    printf("recv client : %s\n", recvBuf);
                } else if(len == 0) {
                    printf("client closed....\n");
                    break;//客户端结束了，需退出循环，否则会继续循环给对方发送数据/写数据（无效且错误的）
                }
                write(cfd, recvBuf, strlen(recvBuf) + 1);//把字符串结束符写入
            }
            close(cfd);
            exit(0);    // 退出当前子进程，需要回收子进程进程，`wait`和`waitpid`
        }

    }
    close(lfd);
    return 0;
}
```

```c
// TCP通信的客户端
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main() {

    // 1.创建套接字
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd == -1) {
        perror("socket");
        exit(-1);
    }

    // 2.连接服务器端
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    inet_pton(AF_INET, "192.168.193.128", &serveraddr.sin_addr.s_addr);
    serveraddr.sin_port = htons(9999);
    int ret = connect(fd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

    if(ret == -1) {
        perror("connect");
        exit(-1);
    }
    
    // 3. 通信
    char recvBuf[1024];
    int i = 0; //发送i的值
    while(1) {
        
        sprintf(recvBuf, "data : %d\n", i++);//转换到recvBuf形式
        
        // 给服务器端发送数据
        //发送数据的时候其实\n是没有发送过去的，因此在这里要把字符结束符带上
        //char recvBuf[1024]={0}进行初始化，下一次发送的时候会带上之前遗留的数据
        write(fd, recvBuf, strlen(recvBuf)+1);

        int len = read(fd, recvBuf, sizeof(recvBuf));
        if(len == -1) {
            perror("read");
            exit(-1);
        } else if(len > 0) {
            printf("recv server : %s\n", recvBuf);
        } else if(len == 0) {
            // 表示服务器端断开连接
            printf("server closed...");
            break; 
        }

        sleep(1);
    }

    // 关闭连接
    close(fd);

    return 0;
}
```

### 多线程实现

多线程和多进程的实现思想是相同的，但是进程和线程是有区别的（内存、内核）。

```c
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

struct sockInfo {
    int fd; // 通信的文件描述符
    struct sockaddr_in addr;
    pthread_t tid;  // 线程号
};

struct sockInfo sockinfos[128]; //设置一个数组，表示最大连接数

void * working(void * arg) {
    // 子线程和客户端通信需要：1、cfd 2、客户端的信息 3、线程号
    // 获取客户端的信息
    struct sockInfo * pinfo = (struct sockInfo *)arg; //强制转换一下

    char cliIp[16];
    inet_ntop(AF_INET, &pinfo->addr.sin_addr.s_addr, cliIp, sizeof(cliIp));
    unsigned short cliPort = ntohs(pinfo->addr.sin_port);
    printf("client ip is : %s, prot is %d\n", cliIp, cliPort);

    // 接收客户端发来的数据
    char recvBuf[1024];
    while(1) {
        int len = read(pinfo->fd, &recvBuf, sizeof(recvBuf));

        if(len == -1) {
            perror("read");
            exit(-1);
        }else if(len > 0) {
            printf("recv client : %s\n", recvBuf);
        } else if(len == 0) {
            printf("client closed....\n");
            break;
        }
        write(pinfo->fd, recvBuf, strlen(recvBuf) + 1);
    }
    close(pinfo->fd);
    pinfo->fd = -1;//重新初始化
    return NULL;
}

int main() {

    // 创建socket
    int lfd = socket(PF_INET, SOCK_STREAM, 0);
    if(lfd == -1){
        perror("socket");
        exit(-1);
    }

    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(9999);
    saddr.sin_addr.s_addr = INADDR_ANY;

    // 绑定
    int ret = bind(lfd,(struct sockaddr *)&saddr, sizeof(saddr));
    if(ret == -1) {
        perror("bind");
        exit(-1);
    }

    // 监听
    ret = listen(lfd, 128);
    if(ret == -1) {
        perror("listen");
        exit(-1);
    }

    // 初始化最大连接数数组数据
    int max = sizeof(sockinfos) / sizeof(sockinfos[0]);
    for(int i = 0; i < max; i++) {
        bzero(&sockinfos[i], sizeof(sockinfos[i]));//被内部成员全部初始化为0
        sockinfos[i].fd = -1; //设置为-1（无效文件描述符），说明可用
        sockinfos[i].tid = -1; //同上
    }

    // 循环等待客户端连接，一旦一个客户端连接进来，就创建一个子线程进行通信
    while(1) {

        struct sockaddr_in cliaddr;
        int len = sizeof(cliaddr);
        // 接受连接
        int cfd = accept(lfd, (struct sockaddr*)&cliaddr, &len);
		
        //局部变量在while循环结束后直接释放，导致线程创建传入的值是无效的
        //如果以堆的形式分配（malloc）的话，会导致在子线程中进行内存管理工作
        //定义为指针
        struct sockInfo * pinfo;
        for(int i = 0; i < max; i++) {
            // 从这个数组中找到一个可以用的sockInfo元素
            if(sockinfos[i].fd == -1) {
                pinfo = &sockinfos[i];
                break;
            }
            if(i == max - 1) { //找不到又是最后一次，那说明不能提供服务，则在这等待
                sleep(1);
                i--;
            }
        }

        pinfo->fd = cfd;
        memcpy(&pinfo->addr, &cliaddr, len);//拷贝

        // 创建子线程，由于pinfo->tid只有线程创建以后才会有（系统分配），因此直接在地址写入参数，这样在生产线程会给结构体变量赋值
        pthread_create(&pinfo->tid, NULL, working, pinfo);

        pthread_detach(pinfo->tid); //回收资源，且是需要不阻塞的，不能使用pthread_join进行回收，设置线程分离pthread_detach
    }

    close(lfd); //关闭文件描述符
    return 0;
}
```

## TCP半关闭状态

即客户端断开连接并收到服务端的回应后，此时服务端还没有进行断开，此时为半关闭状态。



从程序角度，可以使用API来控制实现半连接状态：

```c
#include <sys/socket.h>
int shutdown(int sockfd,int how);
//sockfd:需要关闭的socket描述符
//how:允许为shutdown操作选择以下几种方法
	//SHUT_RD(O):关闭sockfd上的读功能，此选项将不允许sockfd进行读操作。该套接字不再接收数据，任何当前在套接字接受缓冲区的数据将被无声				  的丢弃掉。
    //SHUT_WR(1):关闭sockfd的写功能，此选项将不允许sockfd进行写操作。进程不能在对此套接字发出写操作。
    //SHUT_RDWR(2):关闭sockfd的读写功能。相当于调用shutdown两次:首先是以SHUT_RD,然后以SHUT_WR。

```

使用`close`中止一个连接，但它只是减少描述符的引用计数，并不直接关闭连接，只有当描述符引用计数为0的时候才关闭连接。`shutdown`不考虑描述符的引用计数，直接关闭描述符。也可选择中止一个方向的连接，只中止读或只中止写。



注意:

1. 如果有多个进程共享一个套接字，`close`每被调用一次，计数减1，直到计数为0时，也就是所用进程都调用了`close`，套接字将被释放。
2. 在多进程中如果一个进程调用了`shutdown(sfd,SHUT_RDWR)`后，其它的进程将无法进行通信。但如果一个进程`close(sfd)`将不会影响到其它进程。

## 端口复用

假如有以下的客户端/服务端程序。



在进程结束的时候，但是未彻底断开连接（四次握手全过程），导致端口仍然被socket占据。这种情况出现在服务器端重启/客户端突然断开连接需要重新连接。这里需要进行端口复用。

```c
#include <stdio.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

    // 创建socket
    int lfd = socket(PF_INET, SOCK_STREAM, 0);

    if(lfd == -1) {
        perror("socket");
        return -1;
    }

    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;
    saddr.sin_port = htons(9999);
    
	//设置端口复用
    int optval = 1;
    setsockopt(lfd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));

    // 绑定
    int ret = bind(lfd, (struct sockaddr *)&saddr, sizeof(saddr));
    if(ret == -1) {
        perror("bind");
        return -1;
    }

    // 监听
    ret = listen(lfd, 8);
    if(ret == -1) {
        perror("listen");
        return -1;
    }

    // 接收客户端连接
    struct sockaddr_in cliaddr;
    socklen_t len = sizeof(cliaddr);
    int cfd = accept(lfd, (struct sockaddr *)&cliaddr, &len);
    if(cfd == -1) {
        perror("accpet");
        return -1;
    }

    // 获取客户端信息
    char cliIp[16];
    inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr, cliIp, sizeof(cliIp));
    unsigned short cliPort = ntohs(cliaddr.sin_port);

    // 输出客户端的信息
    printf("client's ip is %s, and port is %d\n", cliIp, cliPort );

    // 接收客户端发来的数据
    char recvBuf[1024] = {0};
    while(1) {
        int len = recv(cfd, recvBuf, sizeof(recvBuf), 0); //这里是socket通信特有的接收数据的方式可指定cfd行为 recv函数族相关
        if(len == -1) {
            perror("recv");
            return -1;
        } else if(len == 0) {
            printf("客户端已经断开连接...\n");
            break;
        } else if(len > 0) {
            printf("read buf = %s\n", recvBuf);
        }

        // 小写转大写
        for(int i = 0; i < len; ++i) {
            recvBuf[i] = toupper(recvBuf[i]);
        }

        printf("after buf = %s\n", recvBuf);

        // 大写字符串发给客户端
        ret = send(cfd, recvBuf, strlen(recvBuf) + 1, 0);
        if(ret == -1) {
            perror("send");
            return -1;
        }
    }
    
    close(cfd);
    close(lfd);

    return 0;
}

```

```c
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {

    // 创建socket
    int fd = socket(PF_INET, SOCK_STREAM, 0);
    if(fd == -1) {
        perror("socket");
        return -1;
    }

    struct sockaddr_in seraddr;
    inet_pton(AF_INET, "127.0.0.1", &seraddr.sin_addr.s_addr);
    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(9999);

    // 连接服务器
    int ret = connect(fd, (struct sockaddr *)&seraddr, sizeof(seraddr));

    if(ret == -1){
        perror("connect");
        return -1;
    }

    while(1) {
        char sendBuf[1024] = {0};
        fgets(sendBuf, sizeof(sendBuf), stdin);//把键盘输入的数据进行读入，阻塞

        write(fd, sendBuf, strlen(sendBuf) + 1);

        // 接收
        int len = read(fd, sendBuf, sizeof(sendBuf));
        if(len == -1) {
            perror("read");
            return -1;
        }else if(len > 0) {
            printf("read buf = %s\n", sendBuf);
        } else {
            printf("服务器已经断开连接...\n");
            break;
        }
    }

    close(fd);

    return 0;
}
```



端口复用最常用的用途是:

- 防止服务器重启时之前绑定的端口还未释放
- 程序突然退出而系统没有释放端口



需要系统API进行设置，不仅可以设置端口复用，也可以用来设置套接字的属性。

```c
#include<sys.types.h>
#include<sys/socket.h>
int setsockopt(int sockfd,int level,int optname,void *optval,socklen_t *optlen)
    //成功返回0，失败返回-1
    //在端口复用的时候，level:OL_SOCKET
    //optname:SO_REUSEPORT或者SO_REUSEADDR
    //optval:端口复用的值，0（不要端口复用）/1（需要端口复用）
    //optlen:optval参数的大小
    //端口复用的时候需要在服务器绑定窗口之前
```

一些参数在`man`文档是没有详细列出，可在`man`的中连接中找到详细内容。



根据《Unix编程》中第七章中有详细介绍。



## IO多路复用

这里是面试和开发的重点，其中`epoll`技术90%可能被问到，其中IO多路复用也叫IO多路转接。



首先重新介绍输入输出的概念。从文件写入内容当中为输入，从内存中读出数据到文件内部为输出。在socket通信的过程当中涉及了大量的输入输出。`socket`其实是一个文件，在内核中有对应的读/写缓冲区，这里的I/O主要是往缓冲区读写数据。



I/O 多路复用使得程序能同时监听多个文件描述符，能够提高程序的性能，Linux 下实现 I/O 多路复用的系统调用主要有 `select`、`poll`和 `epoll`。要求手写，并明白原理。



之前写的程序中，有10个客户端连接进来，是否可以知道哪些客户端给我们发来数据，需要遍历客户端的通信文件描述符来查看其读缓冲区有无数据，是否能进行同时监听每个通信描述符直接知道谁给服务端发送数据。



### IO模型

1. 阻塞等待模型（BIO模型）：当事件为发生的时候一直阻塞，无法允许。因为是阻塞状态，因此不浪费CPU，但同时每次只能处理一个操作，导致效率低。一开始的编程我们只是一个客户端进行连接，后面进行了多进程/线程的设计来解决并发问题，但进程/线程需要消耗一定的系统资源，进程调度需要消耗CPU资源（进程切换）。
2. 非阻塞，忙轮询模型（NIO模型）：非阻塞状态，隔一段时间进行事件是否查询，假如已经发生则处理，提高了程序的执行效率，但是需要占据更多的CPU和系统资源。当出现多个这种状态则需要大量查询。这里使用IO多路转接技术，其中 `select`、`poll`原理类似，而 `epoll`原理不同且效率更高。
   - `select`、`poll`技术：服务器把连接的`socket_fd`以`bite`位记录信息表告诉内核，交给内核检测（调用`select`就回去委托内核检测，内核以指针的形式把以`bite`位进行记录信息表遍历，查看是否有客户端进行数据的发送，当有数据发送的时候置`1`/没有数据发送置`0`，遍历一遍再以`bite`位进行信息记录告诉进程，其实是同一个以`bite`位记录信息表），服务器收到以后进行记录信息表遍历，便可明确哪个客户端发来，查询效率更高。
   - `epoll`技术：服务器把连接的`socket_fd`告诉内核，委托内核生产一个缓冲区专门接收对应的数据，交给内核检测，当收到客户端数据的时候，内核会通知服务端访问缓冲区即可。即传达信息送达，也明确哪个客户端发来。



### `select`函数

`select`技术思想：

1. 首先要构造一个关于文件描述符的列表，将要监听的文件描述符添加到该列表中。

2. 调用一个系统函数，监听该列表中的文件描述符，直到这些描述符中的一个或者多个进行I/O操作时，该函数才返回（转为不阻塞）。

   - 这个函数是阻塞；

   - 函数对文件描述符的检测的操作是由内核完成的；

3. 在返回时，它会告诉进程有多少（哪些）描述符要进行I/O操作。

```c
// sizeof(fd_set) = 128 （字节） 1024（位）标志位，每一个位代表一个文件描述符 0 1 2 默认被用
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/select.h>
int select(int nfds, fd_set *readfds, fd_set *writefds,
fd_set *exceptfds, struct timeval *timeout);
    - 参数：
        - nfds : 委托内核检测的最大文件描述符的值 + 1，比如有文件描述符2 6 11 100则为100+1
        - readfds : 要检测的文件描述符的读的集合，委托内核检测哪些文件描述符的读的属性（内核也有一份），当改变的时候，再返回回来
            - 一般检测读操作
            - 对应的是对方发送过来的数据，因为读是被动的接收数据，检测的就是读缓冲
            区
            - 是一个传入传出参数
        - writefds : 要检测的文件描述符的写的集合，委托内核检测哪些文件描述符的写的属性，检测的是否空余，一般不设置
        	- 委托内核检测写缓冲区是不是还可以写数据（不满的就可以写，满了置0/不满置1）
        - exceptfds : 检测发生异常的文件描述符的集合，一般不设置
        - timeout : 设置的超时时间
        struct timeval {
            long tv_sec; /* seconds */
            long tv_usec; /* microseconds */
        };
        - NULL : 永久阻塞，直到检测到了文件描述符有变化
        - tv_sec = 0 tv_usec = 0， 不阻塞
        - tv_sec > 0 tv_usec > 0， 阻塞对应的时间
    - 返回值 :
        - -1 : 失败
        - >0(n) : 检测的集合中有n个文件描述符发生了变化
// 将参数文件描述符fd对应的标志位设置为0
void FD_CLR(int fd, fd_set *set);
// 判断fd对应的标志位是0还是1， 返回值 ： fd对应的标志位的值，0，返回0， 1，返回1
int FD_ISSET(int fd, fd_set *set);
// 将参数文件描述符fd 对应的标志位，设置为1
void FD_SET(int fd, fd_set *set);
```

```c
//客户端，之前版本
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {

    // 创建socket
    int fd = socket(PF_INET, SOCK_STREAM, 0);
    if(fd == -1) {
        perror("socket");
        return -1;
    }

    struct sockaddr_in seraddr;
    inet_pton(AF_INET, "127.0.0.1", &seraddr.sin_addr.s_addr);
    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(9999);

    // 连接服务器
    int ret = connect(fd, (struct sockaddr *)&seraddr, sizeof(seraddr));

    if(ret == -1){
        perror("connect");
        return -1;
    }

    int num = 0;
    while(1) {
        char sendBuf[1024] = {0};
        sprintf(sendBuf, "send data %d", num++);
        write(fd, sendBuf, strlen(sendBuf) + 1);

        // 接收
        int len = read(fd, sendBuf, sizeof(sendBuf));
        if(len == -1) {
            perror("read");
            return -1;
        }else if(len > 0) {
            printf("read buf = %s\n", sendBuf);
        } else {
            printf("服务器已经断开连接...\n");
            break;
        }
        // sleep(1);
        usleep(1000);
    }

    close(fd);

    return 0;
}
```

```c
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>

int main() {

    // 创建socket
    int lfd = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in saddr;
    saddr.sin_port = htons(9999);
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;

    // 绑定
    bind(lfd, (struct sockaddr *)&saddr, sizeof(saddr));

    // 监听
    listen(lfd, 8);

    // 创建一个fd_set的集合，存放的是需要检测的文件描述符（最多1024个文件描述符），里面是个结构体，实际上是一个数组
    fd_set rdset, tmp; //交给内核修改的是tmp,需要检测是rdset
    FD_ZERO(&rdset);
    FD_SET(lfd, &rdset);
    int maxfd = lfd; //目前最大，假如后面有多个的话需要设置比较出最大的

    while(1) {

        tmp = rdset;

        // 调用select系统函数，让内核帮检测哪些文件描述符有数据
        int ret = select(maxfd + 1, &tmp, NULL, NULL, NULL);
        if(ret == -1) {
            perror("select");
            exit(-1);
        } else if(ret == 0) {
            continue;//继续检测
        } else if(ret > 0) {
            // 说明检测到了有文件描述符的对应的缓冲区的数据发生了改变
            if(FD_ISSET(lfd, &tmp)) {
                // 表示有新的客户端连接进来了
                struct sockaddr_in cliaddr;
                int len = sizeof(cliaddr);
                int cfd = accept(lfd, (struct sockaddr *)&cliaddr, &len);

                // 将新的文件描述符加入到集合中
                FD_SET(cfd, &rdset);

                // 更新最大的文件描述符
                maxfd = maxfd > cfd ? maxfd : cfd;
            }

            for(int i = lfd + 1; i <= maxfd; i++) {
                if(FD_ISSET(i, &tmp)) {
                    // 说明这个文件描述符对应的客户端发来了数据
                    char buf[1024] = {0};
                    int len = read(i, buf, sizeof(buf));
                    if(len == -1) {
                        perror("read");
                        exit(-1);
                    } else if(len == 0) {
                        printf("client closed...\n");
                        close(i);
                        FD_CLR(i, &rdset);
                    } else if(len > 0) {
                        printf("read buf = %s\n", buf);
                        write(i, buf, strlen(buf) + 1);
                    }
                }
            }

        }

    }
    close(lfd);
    return 0;
}
```

### `poll`函数

`select`技术需要用户态/内核态转换，而且需要遍历。每次调用`select`，都需要把`fd`集合从用户态拷贝到内核态，这个开销在`fd`很多时会很大。同时每次调用`select`都需要在内核遍历传递进来的所有`fd`，这个开销在`fd`很多时也很大。`select`支持的文件描述符数量太小了，默认是1024。`fdset`集合不能重用，每次都需要重置。



`poll`技术技术思想：创建`pollfd`结构体，此时虽然和`select`一样需要用户态/内核态转换，但是内核修改的是结构体中的`revents`，解决了固定文件描述符问题/文件描述符集合不能重用问题。

```c
#include <poll.h>
struct pollfd {
    int fd; /* 委托内核检测的文件描述符 */
    short events; /* 委托内核检测文件描述符的什么事件 */
    short revents; /* 文件描述符实际发生的事件 */
};

struct pollfd myfd;
myfd.fd = 5;
myfd.events = POLLIN | POLLOUT; //读/写

int poll(struct pollfd *fds, nfds_t nfds, int timeout);
- 参数：
    - fds : 是一个struct pollfd 结构体数组，这是一个需要检测的文件描述符的集合
    - nfds : 这个是第一个参数数组中最后一个有效元素的下标 + 1
    - timeout : 阻塞时长
        0 : 不阻塞
       -1 : 阻塞，当检测到需要检测的文件描述符有变化，解除阻塞
       >0 : 阻塞的时长
    - 返回值：
       -1 : 失败
       >0（n） : 成功,n表示检测到集合中有n个文件描述符发生变化
```

![image-20240402222734997](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240402222734997.png)



主要关注读事件，其余很少进行设置。

```c
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <poll.h>


int main() {

    // 创建socket
    int lfd = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in saddr;
    saddr.sin_port = htons(9999);
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;

    // 绑定
    bind(lfd, (struct sockaddr *)&saddr, sizeof(saddr));

    // 监听
    listen(lfd, 8);

    // 初始化检测的文件描述符数组，数组的大小可以自己指定（不限）
    struct pollfd fds[1024];
    for(int i = 0; i < 1024; i++) {
        fds[i].fd = -1;
        fds[i].events = POLLIN;
    }
    fds[0].fd = lfd;
    int nfds = 0;

    while(1) {

        // 调用poll系统函数，让内核帮检测哪些文件描述符有数据
        int ret = poll(fds, nfds + 1, -1);
        if(ret == -1) {
            perror("poll");
            exit(-1);
        } else if(ret == 0) {
            continue;
        } else if(ret > 0) {
            // 说明检测到了有文件描述符的对应的缓冲区的数据发生了改变
            if(fds[0].revents & POLLIN) { //可能返回pollin | pollout，因此使用&
                // 表示有新的客户端连接进来了
                struct sockaddr_in cliaddr;
                int len = sizeof(cliaddr);
                int cfd = accept(lfd, (struct sockaddr *)&cliaddr, &len);

                // 将新的文件描述符加入到集合中
                for(int i = 1; i < 1024; i++) {
                    if(fds[i].fd == -1) { //重新找到第一个无效文件符，防止浪费
                        fds[i].fd = cfd;
                        fds[i].events = POLLIN;
                        break;
                    }
                }

                // 更新最大的文件描述符的索引
                nfds = nfds > cfd ? nfds : cfd;
            }

            for(int i = 1; i <= nfds; i++) {//遍历，i是数组索引
                if(fds[i].revents & POLLIN) {
                    // 说明这个文件描述符对应的客户端发来了数据
                    char buf[1024] = {0};
                    int len = read(fds[i].fd, buf, sizeof(buf));
                    if(len == -1) {
                        perror("read");
                        exit(-1);
                    } else if(len == 0) {
                        printf("client closed...\n");
                        close(fds[i].fd);
                        fds[i].fd = -1; //先关闭再置为-1
                    } else if(len > 0) {
                        printf("read buf = %s\n", buf);
                        write(fds[i].fd, buf, strlen(buf) + 1);
                    }
                }
            }

        }

    }
    close(lfd);
    return 0;
}
```

### `epoll`函数

以`epoll_create`在内核创建一个数据结构`eventpoll`，返回值为文件描述符`epfd`（指向该数据结构/内存）。以该`epfd`为基础，使用`epoll`提供的API来操作。



`eventpoll`的数据结构中有两个重要成员`rbr`和`edlist`。

```c
struct eventpoll{
    ...
    struct rb_root rbr;//红黑树，需要检测的文件描述符
    struct list_head rdlist;//双链表，就绪列表，存放数据已经改变的文件描述符
    ...
}
```

不同于`select`/`poll`的拷贝到内核态，而是内核态进行创建（不必进行用户态/内核态进行切换），且使用红黑树（非线性数组），因此效率远比`select`/`poll`更高。调用`epoll_wait`的时候只拷贝了已经被检测事件的文件描述符返回，而非整个数组，效率更高。且返回值不仅是数量也是具体文件描述符（`select`/`poll`返回的只有数量），则只需从整个返回中读取数据即可，效率更高。

```c
#include <sys/epoll.h>
// 创建一个新的epoll实例。在内核中创建了一个数据，这个数据中有两个比较重要的数据，一个是需要检
测的文件描述符的信息（红黑树），还有一个是就绪列表，存放检测到数据发送改变的文件描述符信息（双向
链表）。
int epoll_create(int size);
    - 参数：
    	size : 目前没有意义了。随便写一个数，必须大于0
    - 返回值：
    	-1 : 失败
    	> 0 : 文件描述符，操作epoll实例的
struct epoll_event {
	uint32_t events; /* Epoll events */
	epoll_data_t data; /* User data variable */
};
    常见的Epoll检测事件：
        - EPOLLIN
        - EPOLLOUT
        - EPOLLERR
typedef union epoll_data {
    void *ptr;
    int fd; //这个需要定义
    uint32_t u32;
    uint64_t u64;
} epoll_data_t;
// 对epoll实例进行管理：添加文件描述符信息，删除信息，修改信息
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
    - 参数：
        - epfd : epoll实例对应的文件描述符
        - op : 要进行什么操作
            EPOLL_CTL_ADD: 添加
            EPOLL_CTL_MOD: 修改
            EPOLL_CTL_DEL: 删除
        - fd : 要检测的文件描述符
        - event : 检测文件描述符什么事情（添加的时候需要，删除的时候NULL即可）
// 检测函数，告诉内核从rbr中有无数据发生改变，有改变则把添加到rdlist当中
int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int
timeout);
    - 参数：
        - epfd : epoll实例对应的文件描述符
        - events : 传出参数，保存了发送了变化的文件描述符的信息
        - maxevents : 第二个参数结构体数组的大小
        - timeout : 阻塞时间
            - 0 : 不阻塞
            - -1 : 阻塞，直到检测到fd数据发生变化，解除阻塞
            - > 0 : 阻塞的时长（毫秒）
    - 返回值：
        - 成功，返回发送变化的文件描述符的个数 > 0
        - 失败 -1
```

```c
//server
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>

int main() {

    // 创建监听socket
    int lfd = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in saddr;
    saddr.sin_port = htons(9999);
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;

    // 绑定
    bind(lfd, (struct sockaddr *)&saddr, sizeof(saddr));

    // 监听
    listen(lfd, 8);

    // 调用epoll_create()创建一个epoll实例
    int epfd = epoll_create(100);

    // 将监听的文件描述符相关的检测信息添加到epoll实例中
    struct epoll_event epev;
    // 需要检测的事件位当该文件描述符被写入信息
    epev.events = EPOLLIN;
    // 在epoll_event中的中的epoll_data的fd需要定义
    epev.data.fd = lfd;
    // 加入监听
    epoll_ctl(epfd, EPOLL_CTL_ADD, lfd, &epev);
	
    
    struct epoll_event epevs[1024];

    while(1) {

        int ret = epoll_wait(epfd, epevs, 1024, -1);
        if(ret == -1) {
            perror("epoll_wait");
            exit(-1);
        }

        printf("ret = %d\n", ret);

        for(int i = 0; i < ret; i++) {

            int curfd = epevs[i].data.fd;

            if(curfd == lfd) { 
                //是否是所监听的文件描述符
                // 监听的文件描述符改变说明有客户端连接
                struct sockaddr_in cliaddr;
                int len = sizeof(cliaddr);
                int cfd = accept(lfd, (struct sockaddr *)&cliaddr, &len);
				//重用epev
                epev.events = EPOLLIN | EPOLLOUT;
                epev.data.fd = cfd;
                epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &epev);
            } else {
                //不是监听的文件描述符发生改变则说明是连接的客户端发来数据
                if(epevs[i].events & EPOLLOUT) {
                    //假如epev.events = EPOLLIN|EPOLLOUT,逻辑是不通畅的（只对读），改为直接循环
                    continue;
                }   
                // 有数据到达，需要通信
                char buf[1024] = {0};
                int len = read(curfd, buf, sizeof(buf));
                if(len == -1) {
                    perror("read");
                    exit(-1);
                } else if(len == 0) {
                    printf("client closed...\n");
                    epoll_ctl(epfd, EPOLL_CTL_DEL, curfd, NULL);
                    close(curfd);
                } else if(len > 0) {
                    printf("read buf = %s\n", buf);
                    write(curfd, buf, strlen(buf) + 1);
                }

            }

        }
    }

    close(lfd);
    close(epfd);
    return 0;
}
```

```c
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {

    // 创建socket
    int fd = socket(PF_INET, SOCK_STREAM, 0);
    if(fd == -1) {
        perror("socket");
        return -1;
    }

    struct sockaddr_in seraddr;
    inet_pton(AF_INET, "127.0.0.1", &seraddr.sin_addr.s_addr);
    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(9999);

    // 连接服务器
    int ret = connect(fd, (struct sockaddr *)&seraddr, sizeof(seraddr));

    if(ret == -1){
        perror("connect");
        return -1;
    }

    int num = 0;
    while(1) {
        char sendBuf[1024] = {0};
        sprintf(sendBuf, "send data %d", num++);
        write(fd, sendBuf, strlen(sendBuf) + 1);

        // 接收
        int len = read(fd, sendBuf, sizeof(sendBuf));
        if(len == -1) {
            perror("read");
            return -1;
        }else if(len > 0) {
            printf("read buf = %s\n", sendBuf);
        } else {
            printf("服务器已经断开连接...\n");
            break;
        }
        // sleep(1);
        usleep(1000);
    }

    close(fd);

    return 0;
}

```

### `epoll`的工作模式



LT 模式 （水平触发）

1. 假设委托内核检测读事件 -> 检测`fd`的读缓冲区

2. 读缓冲区有数据 - > `epoll`检测到了会给用户通知

   - 用户不读数据，数据一直在缓冲区，`epoll` 会一直通知

   - 用户只读了一部分数据，`epoll`会通知

   - 缓冲区的数据读完了，不通知

LT（`level - triggered`）是缺省的工作方式，并且同时支持`block`和`no-block socket`。在这种做法中，内核告诉你一个文件描述符是否就绪了，然后你可以对这个就绪的`fd`进行 IO 操作。如果你不作任何操作，内核还是会继续通知你的。

```c
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {

    // 创建socket
    int fd = socket(PF_INET, SOCK_STREAM, 0);
    if(fd == -1) {
        perror("socket");
        return -1;
    }

    struct sockaddr_in seraddr;
    inet_pton(AF_INET, "127.0.0.1", &seraddr.sin_addr.s_addr);
    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(9999);

    // 连接服务器
    int ret = connect(fd, (struct sockaddr *)&seraddr, sizeof(seraddr));

    if(ret == -1){
        perror("connect");
        return -1;
    }

    int num = 0;
    while(1) {
        char sendBuf[1024] = {0};
        // sprintf(sendBuf, "send data %d", num++);
        fgets(sendBuf, sizeof(sendBuf), stdin); //标准输入获取数据

        write(fd, sendBuf, strlen(sendBuf) + 1); //写数据

        // 接收
        int len = read(fd, sendBuf, sizeof(sendBuf));
        if(len == -1) {
            perror("read");
            return -1;
        }else if(len > 0) {
            printf("read buf = %s\n", sendBuf);
        } else {
            printf("服务器已经断开连接...\n");
            break;
        }
    }

    close(fd);

    return 0;
}

```

```c
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>

int main() {

    // 创建socket
    int lfd = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in saddr;
    saddr.sin_port = htons(9999);
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;

    // 绑定
    bind(lfd, (struct sockaddr *)&saddr, sizeof(saddr));

    // 监听
    listen(lfd, 8);

    // 调用epoll_create()创建一个epoll实例
    int epfd = epoll_create(100);

    // 将监听的文件描述符相关的检测信息添加到epoll实例中
    struct epoll_event epev;
    epev.events = EPOLLIN;
    epev.data.fd = lfd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, lfd, &epev);

    struct epoll_event epevs[1024];

    while(1) {

        int ret = epoll_wait(epfd, epevs, 1024, -1);
        if(ret == -1) {
            perror("epoll_wait");
            exit(-1);
        }

        printf("ret = %d\n", ret); //一直通知

        for(int i = 0; i < ret; i++) {

            int curfd = epevs[i].data.fd;

            if(curfd == lfd) {
                // 监听的文件描述符有数据达到，有客户端连接
                struct sockaddr_in cliaddr;
                int len = sizeof(cliaddr);
                int cfd = accept(lfd, (struct sockaddr *)&cliaddr, &len);

                epev.events = EPOLLIN;
                epev.data.fd = cfd;
                epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &epev);
            } else {
                if(epevs[i].events & EPOLLOUT) {
                    continue;
                }   
                // 有数据到达，需要通信
                char buf[5] = {0};
                int len = read(curfd, buf, sizeof(buf));
                if(len == -1) {
                    perror("read");
                    exit(-1);
                } else if(len == 0) {
                    printf("client closed...\n");
                    epoll_ctl(epfd, EPOLL_CTL_DEL, curfd, NULL);
                    close(curfd);
                } else if(len > 0) {
                    printf("read buf = %s\n", buf);
                    write(curfd, buf, strlen(buf) + 1);
                }

            }

        }
    }

    close(lfd);
    close(epfd);
    return 0;
}
```



ET 模式（边沿触发）

1. 假设委托内核检测读事件 -> 检测`fd`的读缓冲区

2. 读缓冲区有数据 - > `epoll`检测到了会给用户通知

   - 用户不读数据，数据一致在缓冲区中，`epoll`下次检测的时候就不通知了

   - 用户只读了一部分数据，`epoll`不通知

   - 缓冲区的数据读完了，不通知

ET（`edge - triggered`）是高速工作方式，只支持`no-block socket`。在这种模式下，当描述\符从未就绪变为就绪时，内核通过`epoll`告诉你。然后它会假设你知道文件描述符已经就绪，并且不会再为那个文件描述符发送更多的就绪通知，直到你做了某些操作导致那个文件描述符不再为就绪状态了。但是请注意，如果一直不对这个 `fd`作 IO 操作（从而导致它再次变成未就绪），内核不会发送更多的通知（only once）。



ET 模式在很大程度上减少了`epoll`事件被重复触发的次数，因此效率要比 LT 模式高。`epoll`工作在 ET 模式的时候，必须使用非阻塞套接口，以避免由于一个文件描述符的阻塞读/阻塞写操作把处理多个文件描述符的任务饿死。



假如边沿触发，需要不断使用`read`去读，当时又会阻塞，因此需要设置为`no-block socket`循环去读。

```c
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <errno.h>

int main() {

    // 创建socket
    int lfd = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in saddr;
    saddr.sin_port = htons(9999);
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;

    // 绑定
    bind(lfd, (struct sockaddr *)&saddr, sizeof(saddr));

    // 监听
    listen(lfd, 8);

    // 调用epoll_create()创建一个epoll实例
    int epfd = epoll_create(100);

    // 将监听的文件描述符相关的检测信息添加到epoll实例中
    struct epoll_event epev;
    epev.events = EPOLLIN;
    epev.data.fd = lfd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, lfd, &epev);

    struct epoll_event epevs[1024];

    while(1) {

        int ret = epoll_wait(epfd, epevs, 1024, -1);
        if(ret == -1) {
            perror("epoll_wait");
            exit(-1);
        }

        printf("ret = %d\n", ret);

        for(int i = 0; i < ret; i++) {

            int curfd = epevs[i].data.fd;

            if(curfd == lfd) {
                // 监听的文件描述符有数据达到，有客户端连接
                struct sockaddr_in cliaddr;
                int len = sizeof(cliaddr);
                int cfd = accept(lfd, (struct sockaddr *)&cliaddr, &len);

                // 设置cfd属性非阻塞
                int flag = fcntl(cfd, F_GETFL);//获取flag
                flag | O_NONBLOCK; //更新flag
                fcntl(cfd, F_SETFL, flag); //设置非阻塞文件描述符

                epev.events = EPOLLIN | EPOLLET;    // 设置边沿触发
                epev.data.fd = cfd;
                epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &epev);
            } else {
                if(epevs[i].events & EPOLLOUT) {
                    continue;
                }  

                // 循环读取出所有数据
                char buf[5];
                int len = 0;
                while( (len = read(curfd, buf, sizeof(buf))) > 0) { //read设置为非阻塞，没有数据的时候可以继续执行
                    // 打印数据
                    // printf("recv data : %s\n", buf);
                    write(STDOUT_FILENO, buf, len);
                    write(curfd, buf, len);
                }
                if(len == 0) {
                    printf("client closed....");
                }else if(len == -1) {
                    if(errno == EAGAIN) { //非阻塞读完了可能产生一个错误提示，但是不应该退出
                        printf("data over.....");
                    }else {
                        perror("read");
                        exit(-1);
                    }
                    
                }

            }

        }
    }

    close(lfd);
    close(epfd);
    return 0;
}
```

## UDP通信

![image-20240403141515857](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240403141515857.png)



```c
#include <sys/types.h>
#include <sys/socket.h>
ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
const struct sockaddr *dest_addr, socklen_t addrlen);
    - 参数：
        - sockfd : 通信的fd
        - buf : 要发送的数据
        - len : 发送数据的长度
        - flags : 0 //不需要了解
        - dest_addr : 通信的另外一端的地址信息
        - addrlen : 地址的内存大小
ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,struct sockaddr *src_addr, socklen_t *addrlen);
    - 参数：
        - sockfd : 通信的fd	
        - buf : 接收数据的数组
        - len : 数组的大小
        - src_addr : 用来保存另外一端的地址信息，不需要可以指定为NULL
		- addrlen : 地址的内存大小
```

```c
//client
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main() {

    // 1.创建一个通信的socket
    int fd = socket(PF_INET, SOCK_DGRAM, 0);
    
    if(fd == -1) {
        perror("socket");
        exit(-1);
    }   

    // 服务器的地址信息
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(9999);
    inet_pton(AF_INET, "127.0.0.1", &saddr.sin_addr.s_addr);

    int num = 0;
    // 3.通信
    while(1) {

        // 发送数据
        char sendBuf[128];
        sprintf(sendBuf, "hello , i am client %d \n", num++);
        sendto(fd, sendBuf, strlen(sendBuf) + 1, 0, (struct sockaddr *)&saddr, sizeof(saddr));

        // 接收数据
        int num = recvfrom(fd, sendBuf, sizeof(sendBuf), 0, NULL, NULL);//以文件描述符进行数据接收，可以置null
        printf("server say : %s\n", sendBuf);

        sleep(1);
    }

    close(fd);
    return 0;
}
```

```c
//server
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main() {

    // 1.创建一个通信的socket
    int fd = socket(PF_INET, SOCK_DGRAM, 0); //数据报形式
    
    if(fd == -1) {
        perror("socket");
        exit(-1);
    }   

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9999);
    addr.sin_addr.s_addr = INADDR_ANY;

    // 2.绑定
    int ret = bind(fd, (struct sockaddr *)&addr, sizeof(addr));
    if(ret == -1) {
        perror("bind");
        exit(-1);
    }

    // 3.通信
    while(1) {
        char recvbuf[128];
        char ipbuf[16];

        struct sockaddr_in cliaddr;
        int len = sizeof(cliaddr);

        // 接收数据
        int num = recvfrom(fd, recvbuf, sizeof(recvbuf), 0, (struct sockaddr *)&cliaddr, &len);

        printf("client IP : %s, Port : %d\n", 
            inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr, ipbuf, sizeof(ipbuf)),
            ntohs(cliaddr.sin_port));

        printf("client say : %s\n", recvbuf);

        // 发送数据
        sendto(fd, recvbuf, strlen(recvbuf) + 1, 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));

    }

    close(fd);
    return 0;
}
```

### 广播

向子网中多台计算机发送消息，并且子网中所有的计算机都可以接收到发送方发送的消息，每个广播消息都包含一个特殊的IP地址，这个IP中子网内主机标志部分的二进制全部为1。

a. 只能在局域网中使用。

b. 客户端需要绑定服务器广播使用的端口，才可以接收到广播消息。 



客户端绑定同一个端口，作为广播的关键，是服务器广播数据的端口。

```c
// 设置广播属性的函数
int setsockopt(int sockfd, int level, int optname,const void *optval, socklen_t
optlen);
    - sockfd : 文件描述符
    - level : SOL_SOCKET
    - optname : SO_BROADCAST
    - optval : int类型的值，为1表示允许广播
    - optlen : optval的大小
```

```c
//client
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main() {

    // 1.创建一个通信的socket
    int fd = socket(PF_INET, SOCK_DGRAM, 0);
    if(fd == -1) {
        perror("socket");
        exit(-1);
    }   

    struct in_addr in;

    // 2.客户端绑定本地的IP和端口
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9999);
    addr.sin_addr.s_addr = INADDR_ANY;

    int ret = bind(fd, (struct sockaddr *)&addr, sizeof(addr));
    if(ret == -1) {
        perror("bind");
        exit(-1);
    }

    // 3.通信
    while(1) {
        
        char buf[128];
        // 接收数据
        int num = recvfrom(fd, buf, sizeof(buf), 0, NULL, NULL);
        printf("server say : %s\n", buf);

    }

    close(fd);
    return 0;
}
```

```c
//server
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main() {

    // 1.创建一个通信的socket
    int fd = socket(PF_INET, SOCK_DGRAM, 0);
    if(fd == -1) {
        perror("socket");
        exit(-1);
    }   

    // 2.设置广播属性
    int op = 1;
    setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &op, sizeof(op));
    
    // 3.创建一个广播的地址
    struct sockaddr_in cliaddr;
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_port = htons(9999);
    inet_pton(AF_INET, "192.168.193.255", &cliaddr.sin_addr.s_addr);//本地IP

    // 3.通信
    int num = 0;
    while(1) {
       
        char sendBuf[128];
        sprintf(sendBuf, "hello, client....%d\n", num++);
        // 发送数据
        sendto(fd, sendBuf, strlen(sendBuf) + 1, 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
        printf("广播的数据：%s\n", sendBuf);
        sleep(1);
    }

    close(fd);
    return 0;
}
```

### 组播

单播地址标识单个 IP 接口，广播地址标识某个子网的所有 IP 接口，多播地址标识一组 IP 接口。单播和广播是寻址方案的两个极端（要么单个要么全部），多播则意在两者之间提供一种折中方案。多播数据报只应该由对它感兴趣的接口接收，也就是说由运行相应多播会话应用系统的主机上的接口接收。另外，广播一般局限于局域网内使用，而多播则既可以用于局域网，也可以跨广域网使用。了解即可，开发中很少使用。

a. 组播既可以用于局域网，也可以用于广域网

b. 客户端需要加入多播组，才能接收到多播的数据



IP 多播通信必须依赖于 IP 多播地址，在 IPv4 中它的范围从 224.0.0.0 到 239.255.255.255 ，并被划分为局部链接多播地址、预留多播地址和管理权限多播地址三类:

| **IP**地址                | **说明**                                                   |
| ------------------------- | ---------------------------------------------------------- |
| 224.0.0.0~224.0.0.255     | 局部链接多播地址：是为路由协议和其它用途保留的地址，路由   |
| 224.0.1.0~224.0.1.255     | 预留多播地址：公用组播地址，可用于Internet；使用前需要申请 |
| 224.0.2.0~238.255.255.255 | 预留多播地址：用户可用组播地址(临时组地址)，全网范围内有效 |
| 239.0.0.0~239.255.255.255 | 本地管理组播地址，可供组织内部使用，类似于私有 IP 地址，不 |

```c
int setsockopt(int sockfd, int level, int optname,const void *optval,
socklen_t optlen);
    // 服务器设置多播的信息，外出接口
        - level : IPPROTO_IP
        - optname : IP_MULTICAST_IF
        - optval : struct in_addr
    // 客户端加入到多播组：
        - level : IPPROTO_IP
        - optname : IP_ADD_MEMBERSHIP
        - optval : struct ip_mreq
struct ip_mreq
{
    /* IP multicast address of group. */
    struct in_addr imr_multiaddr; // 组播的IP地址
    /* Local IP address of interface. */
    struct in_addr imr_interface; // 本地的IP地址
};
typedef uint32_t in_addr_t;
struct in_addr
{
    in_addr_t s_addr;
};
```

```c
//client
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main() {

    // 1.创建一个通信的socket
    int fd = socket(PF_INET, SOCK_DGRAM, 0);
    if(fd == -1) {
        perror("socket");
        exit(-1);
    }   

    struct in_addr in;
    // 2.客户端绑定本地的IP和端口
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9999);
    addr.sin_addr.s_addr = INADDR_ANY;

    int ret = bind(fd, (struct sockaddr *)&addr, sizeof(addr));
    if(ret == -1) {
        perror("bind");
        exit(-1);
    }

    struct ip_mreq op;
    inet_pton(AF_INET, "239.0.0.10", &op.imr_multiaddr.s_addr);
    op.imr_interface.s_addr = INADDR_ANY;

    // 加入到多播组
    setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &op, sizeof(op));

    // 3.通信
    while(1) {
        
        char buf[128];
        // 接收数据
        int num = recvfrom(fd, buf, sizeof(buf), 0, NULL, NULL);
        printf("server say : %s\n", buf);

    }

    close(fd);
    return 0;
}
```

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main() {

    // 1.创建一个通信的socket
    int fd = socket(PF_INET, SOCK_DGRAM, 0);
    if(fd == -1) {
        perror("socket");
        exit(-1);
    }   

    // 2.设置多播的属性，设置外出接口
    struct in_addr imr_multiaddr;
    // 初始化多播地址
    inet_pton(AF_INET, "239.0.0.10", &imr_multiaddr.s_addr);
    setsockopt(fd, IPPROTO_IP, IP_MULTICAST_IF, &imr_multiaddr, sizeof(imr_multiaddr));
    
    // 3.初始化客户端的地址信息
    struct sockaddr_in cliaddr;
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_port = htons(9999);
    inet_pton(AF_INET, "239.0.0.10", &cliaddr.sin_addr.s_addr);//上表格多播地址

    // 3.通信
    int num = 0;
    while(1) {
       
        char sendBuf[128];
        sprintf(sendBuf, "hello, client....%d\n", num++);
        // 发送数据
        sendto(fd, sendBuf, strlen(sendBuf) + 1, 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
        printf("组播的数据：%s\n", sendBuf);
        sleep(1);
    }

    close(fd);
    return 0;
}
```

## 本地套接字

本地套接字的作用：本地的进程间通信、有关系的进程间的通信、没有关系的进程间的通信。



本地套接字实现流程和网络套接字类似，一般呢采用TCP的通信流程。



```c
// 本地套接字通信的流程 - tcp
// 服务器端
1. 创建监听的套接字
    int lfd = socket(AF_UNIX/AF_LOCAL, SOCK_STREAM, 0);
2. 监听的套接字绑定本地的套接字文件 -> server端
    struct sockaddr_un addr;
    // 绑定成功之后，指定的sun_path中的套接字文件会自动生成。
    bind(lfd, addr, len);
3. 监听
    listen(lfd, 100);
4. 等待并接受连接请求
    struct sockaddr_un cliaddr;
    int cfd = accept(lfd, &cliaddr, len);
5. 通信
    接收数据：read/recv
    发送数据：write/send
6. 关闭连接
	close();
    // 客户端的流程
    1. 创建通信的套接字
    int fd = socket(AF_UNIX/AF_LOCAL, SOCK_STREAM, 0);
2. 监听的套接字绑定本地的IP 端口
    struct sockaddr_un addr;
    // 绑定成功之后，指定的sun_path中的套接字文件会自动生成。
    bind(lfd, addr, len);
3. 连接服务器
    struct sockaddr_un serveraddr;
    connect(fd, &serveraddr, sizeof(serveraddr));
4. 通信
    接收数据：read/recv
    发送数据：write/send
5. 关闭连接
    close();
```

```c
// 头文件: sys/un.h
#define UNIX_PATH_MAX 108
struct sockaddr_un {
sa_family_t sun_family; // 地址族协议 af_local
char sun_path[UNIX_PATH_MAX]; // 套接字文件的路径, 这是一个伪文件, 大小永远=0
};
```



![image-20240403154420478](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240403154420478.png)





不同于网络套接字，这里使用的是`sockaddr_un`结构。



在设计思想中，对应`sever.sock`和`client.sock`两个内核文件，文件内部分为读缓存和写缓存。通过套接字进行对彼此缓冲区内容读写。

```c
//client
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/un.h>

int main() {

    unlink("client.sock"); //但是每次都需要重新绑定`server.sock`/`client.sock`，删除

    // 1.创建套接字
    int cfd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if(cfd == -1) {
        perror("socket");
        exit(-1);
    }

    // 2.绑定本地套接字文件
    struct sockaddr_un addr;
    addr.sun_family = AF_LOCAL;
    strcpy(addr.sun_path, "client.sock");
    int ret = bind(cfd, (struct sockaddr *)&addr, sizeof(addr));
    if(ret == -1) {
        perror("bind");
        exit(-1);
    }

    // 3.连接服务器
    struct sockaddr_un seraddr;
    seraddr.sun_family = AF_LOCAL;
    strcpy(seraddr.sun_path, "server.sock"); 
    ret = connect(cfd, (struct sockaddr *)&seraddr, sizeof(seraddr));
    if(ret == -1) {
        perror("connect");
        exit(-1);
    }

    // 4.通信
    int num = 0;
    while(1) {

        // 发送数据
        char buf[128];
        sprintf(buf, "hello, i am client %d\n", num++);
        send(cfd, buf, strlen(buf) + 1, 0);
        printf("client say : %s\n", buf);

        // 接收数据
        int len = recv(cfd, buf, sizeof(buf), 0);

        if(len == -1) {
            perror("recv");
            exit(-1);
        } else if(len == 0) {
            printf("server closed....\n");
            break;
        } else if(len > 0) {
            printf("server say : %s\n", buf);
        }

        sleep(1);

    }

    close(cfd);
    return 0;
}
```

```c
//server
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/un.h>

int main() {

    unlink("server.sock");//但是每次都需要重新绑定`server.sock`/`client.sock`，删除

    // 1.创建监听的套接字
    int lfd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if(lfd == -1) {
        perror("socket");
        exit(-1);
    }

    // 2.绑定本地套接字文件
    struct sockaddr_un addr;
    addr.sun_family = AF_LOCAL;
    strcpy(addr.sun_path, "server.sock");
    int ret = bind(lfd, (struct sockaddr *)&addr, sizeof(addr));
    if(ret == -1) {
        perror("bind");
        exit(-1);
    }

    // 3.监听
    ret = listen(lfd, 100);
    if(ret == -1) {
        perror("listen");
        exit(-1);
    }

    // 4.等待客户端连接
    struct sockaddr_un cliaddr;
    int len = sizeof(cliaddr);
    int cfd = accept(lfd, (struct sockaddr *)&cliaddr, &len);
    if(cfd == -1) {
        perror("accept");
        exit(-1);
    }

    printf("client socket filename: %s\n", cliaddr.sun_path);

    // 5.通信
    while(1) {

        char buf[128];
        int len = recv(cfd, buf, sizeof(buf), 0);

        if(len == -1) {
            perror("recv");
            exit(-1);
        } else if(len == 0) {
            printf("client closed....\n");
            break;
        } else if(len > 0) {
            printf("client say : %s\n", buf);
            send(cfd, buf, len, 0);
        }

    }

    close(cfd);
    close(lfd);

    return 0;
}
```



# Web服务器开发

## 阻塞/非阻塞、同步/异步

典型的一次IO两个阶段：数据就绪和数据读写。



数据就绪：根据系统IO操作的就绪状态（检查数据有没有过来）

- 阻塞，调用IO方法的线程进入阻塞状态
- 非阻塞，不会改变线程的状态，以返回值进行判断对方的状态

如`ssize_t recv(int sockfd,void *buf,size_t len,int flag)`是一个接收数据的函数，其中`sockfd`（默认是阻塞的）对应了一个内核的TCP缓冲区。非阻塞下立即返回一个值，则根据返回值进行判断。当返回`-1`的时候，又有`EINTR`、`EEAGAIN`  、`EWOULDBLOCK` 。当返回`0`的时候说明读到数据文件的末尾，对方连接关闭。当返回`>0`，读取了多少数据。





数据读写：根据应用程序和内核的交互方式（进行数据的进行读/写）

- 同步
- 异步（Linux中的`AIO`，window中的`IOCP`)

同样以如`ssize_t recv(int sockfd,void *buf,size_t len,int flag)`是一个接收数据的函数。这是主动传递一个数组中进行数据传递，这是一个主动的行为，从`sockfd`（默认是阻塞的）对应了一个内核的TCP缓冲区搬数据（应用层自己搬）。异步显然比同步效率更高，但是实现确实相当复杂，只能看操作系统是否提供一个`API`给调用进行搬运，需要提供`sockfd`、`buf`、通知方式。当内核收到数据后，会帮把数据放入`buf`（操作系统自己搬）再通知。



处理IO的时候，阻塞和非阻塞都是同步的IO，只有使用了特殊API才是异步IO。

## Unix、Linux上的五种IO模型

一、阻塞blocking



调用者调用了某个函数，等待这个函数返回，期间什么也不做，不停的去检查这个函数有没有返回，必须等这个函数返回才能进行下一步动作。是文件描述符的行为，可以对文件描述符的行为。



![image-20240408101930309](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240408101930309.png)

二、非阻塞 non-blocking（NIO）



非阻塞等待，每隔一段时间就去检测IO事件是否就绪。没有就绪就可以做其他事。非阻塞I/O执行系统调用总是立即返回，不管事件是否已经发生，若事件没有发生，则返回-1，此时可以根据 `errno` 区分这两种情况，对于`accept`，`recv` 和 `send`，事件未发生时，`errno` 通常被设置成 `EAGAIN`。目的是在单进程/线程中一次可以检测一个客户端事件。



![image-20240408102100047](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240408102100047.png)

三、IO复用（IO multiplexing）



Linux 用 `select`/`poll`/`epoll` 函数实现 IO 复用模型，这些函数也会使进程阻塞，但是和阻塞IO所不同的是这些函数可以同时阻塞多个IO操作。而且可以同时对多个读操作、写操作的IO函数进行检测。直到有数据可读或可写时，才真正调用IO操作函数。目的是在单进程/线程中一次可以检测多个客户端事件，高并发是是需要多进程多线程开发。



![image-20240408102219129](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240408102219129.png)

四、信号驱动（signal-driven）



Linux 用套接口进行信号驱动 IO，安装一个信号处理函数，进程继续运行并不阻塞，当IO事件就绪，进程收到SIGIO信号，然后处理 IO 事件（回调信号处理函数）。



![image-20240408102317824](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240408102317824.png)



内核在第一个阶段是异步，在第二个阶段是同步；与非阻塞IO的区别在于它提供了消息通知机制，不需要用户进程不断的轮询检查，减少了系统API的调用次数，提高了效率。 



五、异步（asynchronous）



Linux中，可以调用 `aio_read` 函数告诉内核描述字缓冲区指针和缓冲区的大小、文件偏移及通知的方式，然后立即返回，当内核将数据拷贝到缓冲区后，再通知应用程序。



![image-20240408102450810](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240408102450810.png)



```c
/* Asynchronous I/O control block. */
struct aiocb
{
    int aio_fildes; /* File desriptor. */
    int aio_lio_opcode; /* Operation to be performed. */
    int aio_reqprio; /* Request priority offset. */
    volatile void *aio_buf; /* Location of buffer. */
    size_t aio_nbytes; /* Length of transfer. */
    struct sigevent aio_sigevent; /* Signal number and value. */
    
    /* Internal members. */
    struct aiocb *__next_prio;
    int __abs_prio;
    int __policy;
    int __error_code;
    __ssize_t __return_value;
    
    #ifndef __USE_FILE_OFFSET64
        __off_t aio_offset; /* File offset. */
        char __pad[sizeof (__off64_t) - sizeof (__off_t)];
    #else
        __off64_t aio_offset; /* File offset. */
    #endif
        char __glibc_reserved[32];
};
```

在本项目中使用IO多路复用和非阻塞模型。

## Web Server(网页服务器)

一个 Web Server 就是一个服务器软件（程序），或者是运行这个服务器软件的硬件（计算机）。其主要功能是通过 HTTP 协议与客户端（通常是浏览器（Browser））进行通信，来接收，存储，处理来自客户端的 HTTP 请求，并对其请求做出 HTTP 响应，返回给客户端其请求的内容（文件、网页等）或返

回一个 Error 信息。



通常用户使用 Web 浏览器与相应服务器进行通信。在浏览器中键入“域名”或“IP地址:端口号”，浏览器则先将你的域名解析成相应的 IP 地址或者直接根据你的IP地址向对应的 Web 服务器发送一个 HTTP 请求。这一过程首先要通过 TCP 协议的三次握手建立与目标 Web 服务器的连接，然后 HTTP 协议生成针对目标 Web 服务器的 HTTP 请求报文，通过 TCP、IP 等协议发送到目标 Web 服务器上。



![image-20240408111231469](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240408111231469.png)



## HTTP协议

超文本传输协议（Hypertext Transfer Protocol，HTTP）是一个简单的请求 - 响应协议，它通常运行在TCP 之上。它指定了客户端可能发送给服务器什么样的消息以及得到什么样的响应。请求和响应消息的头以 ASCII 形式给出；而消息内容则具有一个类似 MIME 的格式。HTTP是万维网的数据通信的基础。



HTTP 是一个客户端终端（用户）和服务器端（网站）请求和应答的标准（TCP）。通过使用网页浏览器、网络爬虫或者其它的工具，客户端发起一个HTTP请求到服务器上指定端口（默认端口为`80`，不需要显式写上端口）。



HTTP 协议定义 Web 客户端如何从 Web 服务器请求 Web 页面，以及服务器如何把 Web 页面传送给客户端。HTTP 协议采用了请求/响应模型。客户端向服务器发送一个请求报文，请求报文包含请求的方法、URL、协议版本、请求头部和请求数据。服务器以一个状态行作为响应，响应的内容包括协议的版本、成功或者错误代码、服务器信息、响应头部和响应数据。



以下是 HTTP 请求/响应的步骤：

1. 客户端连接到 Web 服务器

一个HTTP客户端，通常是浏览器，与 Web 服务器的 HTTP 端口（默认为 80 ）建立一个 TCP 套接字连接。例如，http://www.baidu.com。（URL）

2. 发送 HTTP 请求

通过 TCP 套接字，客户端向 Web 服务器发送一个文本的请求报文，一个请求报文由请求行、请求头部、空行和请求数据 4 部分组成。

3. 服务器接受请求并返回 HTTP 响应

Web 服务器解析请求，定位请求资源。服务器将资源复本写到 TCP 套接字，由客户端读取。一个响应由状态行、响应头部、空行和响应数据 4 部分组成。

4. 释放连接 TCP 连接

若 connection 模式为 close，则服务器主动关闭 TCP连接，客户端被动关闭连接，释放 TCP 连接；若connection 模式为 keepalive，则该连接会保持一段时间，在该时间内可以继续接收请求;

5. 客户端浏览器解析 HTML 内容

客户端浏览器首先解析状态行，查看表明请求是否成功的状态代码。然后解析每一个响应头，响应头告知以下为若干字节的 HTML 文档和文档的字符集。客户端浏览器读取响应数据 HTML，根据HTML 的语法对其进行格式化，并在浏览器窗口中显示。



例如：在浏览器地址栏键入URL，按下回车之后会经历以下流程：

1. 浏览器向 DNS 服务器请求解析该 URL 中的域名所对应的 IP 地址;
2. 解析出 IP 地址后，根据该 IP 地址和默认端口 80，和服务器建立 TCP 连接;
3. 浏览器发出读取文件（ URL 中域名后面部分对应的文件）的 HTTP 请求，该请求报文作为 TCP 三

次握手的第三个报文的数据发送给服务器;

4. 服务器对浏览器请求作出响应，并把对应的 HTML 文本发送给浏览器;
5. 释放 TCP 连接;
6. 浏览器将该 HTML 文本并显示内容



HTTP 协议是基于 TCP/IP 协议之上的应用层协议，基于 请求-响应 的模式。HTTP 协议规定，请求从客户端发出，最后服务器端响应该请求并返回。换句话说，肯定是先从客户端开始建立通信的，服务器端在没有接收到请求之前不会发送响应。



![image-20240408112539652](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240408112539652.png)



### 请求报文



其中，请求报文的格式如下。



![image-20240408112621755](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240408112621755.png)

GET / HTTP/1.1 



Host: www.baidu.com

User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:86.0) Gecko/20100101 Firefox/86.0

Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8

Accept-Language: zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2

Accept-Encoding: gzip, deflate, br

Connection: keep-alive

Cookie: BAIDUID=6729CB682DADC2CF738F533E35162D98:FG=1;

BIDUPSID=6729CB682DADC2CFE015A8099199557E; PSTM=1614320692; BD_UPN=13314752;

BDORZ=FFFB88E999055A3F8A630C64834BD6D0;

__yjs_duid=1_d05d52b14af4a339210722080a668ec21614320694782; BD_HOME=1;

H_PS_PSSID=33514_33257_33273_31660_33570_26350;

BA_HECTOR=8h2001alag0lag85nk1g3hcm60q

Upgrade-Insecure-Requests: 1

Cache-Control: max-age=0



其中，响应报文的格式如下。

![image-20240408112706733](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240408112706733.png)

HTTP/1.1 200 OK



Bdpagetype: 1

Bdqid: 0xf3c9743300024ee4

Cache-Control: private

Connection: keep-alive

Content-Encoding: gzip

Content-Type: text/html;charset=utf-8

Date: Fri, 26 Feb 2021 08:44:35 GMT

Expires: Fri, 26 Feb 2021 08:44:35 GMT

Server: BWS/1.1

Set-Cookie: BDSVRTM=13; path=/

Set-Cookie: BD_HOME=1; path=/

Set-Cookie: H_PS_PSSID=33514_33257_33273_31660_33570_26350; path=/; domain=.baidu.com

Strict-Transport-Security: max-age=172800

Traceid: 1614329075128412289017566699583927635684

X-Ua-Compatible: IE=Edge,chrome=1

Transfer-Encoding: chunked

### HTTP状态码



所有HTTP响应的第一行都是状态行，依次是当前HTTP版本号，3位数字组成的状态代码，以及描述状态的短语，彼此由空格分隔。



状态代码的第一个数字代表当前响应的类型：

1. 1xx消息——请求已被服务器接收，继续处理
2. 2xx成功——请求已成功被服务器接收、理解、并接受
3. 3xx重定向——需要后续操作才能完成这一请求
4. 4xx请求错误——请求含有词法错误或者无法被执行
5. 5xx服务器错误——服务器在处理某个正确请求时发生错误



虽然 RFC 2616 中已经推荐了描述状态的短语，例如"200 OK"，"404 Not Found"，但是WEB开发者仍然能够自行决定采用何种短语，用以显示本地化的状态描述或者自定义信息。



### HTTP请求方法



HTTP/1.1 协议中共定义了八种方法（也叫“动作”）来以不同方式操作指定的资源：

1. GET：向指定的资源发出“显示”请求。使用 GET 方法应该只用在读取数据，而不应当被用于产生“副作用”的操作中，例如在 Web Application 中。其中一个原因是 GET 可能会被网络蜘蛛等随意访问。

2. HEAD：与 GET 方法一样，都是向服务器发出指定资源的请求。只不过服务器将不传回资源的本文部分。它的好处在于，使用这个方法可以在不必传输全部内容的情况下，就可以获取其中“关于该资源的信息”（元信息或称元数据）。

3. POST：向指定资源提交数据，请求服务器进行处理（例如提交表单或者上传文件）。数据被包含在请求本文中。这个请求可能会创建新的资源或修改现有资源，或二者皆有。

4. PUT：向指定资源位置上传其最新内容。
5. DELETE：请求服务器删除 Request-URI 所标识的资源。
6. TRACE：回显服务器收到的请求，主要用于测试或诊断。
7. OPTIONS：这个方法可使服务器传回该资源所支持的所有 HTTP 请求方法。用'*'来代替资源名称，向 Web 服务器发送 OPTIONS 请求，可以测试服务器功能是否正常运作。

8. CONNECT：HTTP/1.1 协议中预留给能够将连接改为管道方式的代理服务器。通常用于SSL加密服务器的链接（经由非加密的 HTTP 代理服务器）。



其中`GET`和`POST`是最常用的两种方法。本项目中需要实现`GET`请求。



## 服务器编程基本框架



虽然服务器程序种类繁多，但其基本框架都一样，不同之处在于逻辑处理。



![image-20240408113938920](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240408113938920.png)



![image-20240408114226290](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240408114226290.png)



I/O 处理单元是服务器管理客户连接的模块。它通常要完成以下工作：等待并接受新的客户连接，接收客户数据，将服务器响应数据返回给客户端。但是数据的收发不一定在 I/O 处理单元中执行，也可能在逻辑单元中执行，具体在何处执行取决于事件处理模式。



一个逻辑单元通常是一个进程或线程。它分析并处理客户数据，然后将结果传递给 I/O 处理单元或者直接发送给客户端（具体使用哪种方式取决于事件处理模式）。服务器通常拥有多个逻辑单元，以实现对多个客户任务的并发处理。



网络存储单元可以是数据库、缓存和文件，但不是必须的。



请求队列是各单元之间的通信方式的抽象。I/O 处理单元接收到客户请求时，需要以某种方式通知一个逻辑单元来处理该请求。同样，多个逻辑单元同时访问一个存储单元时，也需要采用某种机制来协调处理竞态条件。请求队列通常被实现为池（进程池、线程池）的一部分。



## 两种高效的事件处理模式

服务器程序通常需要处理三类事件：I/O 事件、信号及定时事件。有两种高效的事件处理模式：`Reactor` 和 `Proactor`，同步 I/O 模型通常用于实现 `Reactor` 模式，异步 I/O 模型通常用于实现 `Proactor` 模式。其中I/O事件是重中之重。



- 在 Linux 下的异步 I/O 是不完善的，`AIO` 系列函数是由 `POSIX` 定义的异步操作接口，不是真正的操作系统级别支持的，而是在用户空间模拟出来的异步，并且仅仅支持基于本地文件的 `AIO` 异步操作，网络编程中的 `socket` 是不支持的，这也使得基于 Linux 的高性能网络程序都是使用 Reactor 方案。
-  而 Windows 里实现了一套完整的支持 `socket` 的异步编程接口，这套接口就是 `IOCP`，是由操作系统级别实现的异步 I/O，真正意义上异步 I/O，因此在 Windows 里实现高性能网络程序可以使用效率更高的 `Proactor` 方案。

### `Reactor`模式

要求主线程（I/O处理单元）只负责监听文件描述符上是否有事件发生，有的话就立即将该事件通知工作线程（逻辑单元），将 socket 可读可写事件放入请求队列，交给工作线程处理，工作线程负责业务逻辑、读/写。除此之外，主线程不做任何其他实质性的工作。读写数据，接受新的连接，以及处理客户请求均在工作线程中完成。使用同步 I/O（以 `epoll_wait` 为例）实现的 Reactor 模式的工作流程是：

1. 主线程往 `epoll` 内核事件表中注册 socket 上的读就绪事件。
2. 主线程调用 `epoll_wait` 等待 socket 上有数据可读。
3. 当 socket 上有数据可读时， `epoll_wait` 通知主线程。主线程则将 socket 可读事件放入请求队列。
4.  睡眠在请求队列上的某个工作线程被唤醒，它从 socket 读取数据，并处理客户请求，然后往 `epoll`内核事件表中注册该 socket 上的写就绪事件。

5. 当主线程调用 `epoll_wait` 等待 socket 可写。

6. 当 socket 可写时，`epoll_wait` 通知主线程。主线程将 socket 可写事件放入请求队列。

7. 睡眠在请求队列上的某个工作线程被唤醒，它往 socket 上写入服务器处理客户请求的结果。

   

![image-20240408115536336](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240408115536336.png)



本项目以线程举例表示该模式的工作流程。



### `Proactor`模式

`Proactor` 模式将所有 I/O 操作都交给主线程和内核来处理（进行读、写），工作线程仅仅负责业务逻辑。使用异步 I/O 模型（以 `aio_read` 和 `aio_write` 为例）实现的 `Proactor` 模式的工作流程是：

1. 主线程调用 aio_read 函数向内核注册 socket 上的读完成事件，并告诉内核用户读缓冲区的位置，以及读操作完成时如何通知应用程序（这里以信号为例）。

2. 主线程继续处理其他逻辑。
3. 当 socket 上的数据被读入用户缓冲区后，内核将向应用程序发送一个信号，以通知应用程序数据已经可用。

4. 应用程序预先定义好的信号处理函数选择一个工作线程来处理客户请求。工作线程处理完客户请求后，调用 aio_write 函数向内核注册 socket 上的写完成事件，并告诉内核用户写缓冲区的位置，以及写操作完成时如何通知应用程序。

5. 主线程继续处理其他逻辑。
6. 当用户缓冲区的数据被写入 socket 之后，内核将向应用程序发送一个信号，以通知应用程序数据已经发送完毕。

7. 应用程序预先定义好的信号处理函数选择一个工作线程来做善后处理，比如决定是否关闭 socket。



![image-20240408120051668](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240408120051668.png)

### 模拟 `Proactor` 模式

使用同步 I/O 方式模拟出 `Proactor` 模式。原理是：主线程执行数据读写操作，读写完成之后，主线程向工作线程通知这一”完成事件“。那么从工作线程的角度来看，它们就直接获得了数据读写的结果，接下来要做的只是对读写的结果进行逻辑处理。



使用同步 I/O 模型（以 `epoll_wait`为例）模拟出的 `Proactor` 模式的工作流程如下：

1. 主线程往 `epoll` 内核事件表中注册 socket 上的读就绪事件。
2. 主线程调用 `epoll_wait` 等待 socket 上有数据可读。
3. 当 socket 上有数据可读时，`epoll_wait` 通知主线程。主线程从 socket 循环读取数据，直到没有更多数据可读，然后将读取到的数据封装成一个请求对象并插入请求队列。

4. 睡眠在请求队列上的某个工作线程被唤醒，它获得请求对象并处理客户请求，然后往 `epoll` 内核事件表中注册 socket 上的写就绪事件。

5. 主线程调用 `epoll_wait` 等待 socket 可写。
6. 当 socket 可写时，`epoll_wait` 通知主线程。主线程往 socket 上写入服务器处理客户请求的结果。



![image-20240408121053499](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240408121053499.png)



## 线程池

线程池是由服务器预先创建的一组子线程，线程池中的线程数量应该和 CPU 数量差不多。线程池中的所有子线程都运行着相同的代码。当有新的任务到来时，主线程将通过某种方式选择线程池中的某一个子线程来为之服务。相比与动态的创建子线程，选择一个已经存在的子线程的代价显然要小得多。至于主线程选择哪个子线程来为新任务服务，则有多种方式：

- 主线程使用某种算法来主动选择子线程。最简单、最常用的算法是随机算法和 Round Robin（轮流选取）算法，但更优秀、更智能的算法将使任务在各个工作线程中更均匀地分配，从而减轻服务器的整体压力。

- 主线程和所有子线程通过一个共享的工作队列来同步，子线程都睡眠在该工作队列上。当有新的任务到来时，主线程将任务添加到工作队列中。这将唤醒正在等待任务的子线程，不过只有一个子线程将获得新任务的”接管权“，它可以从工作队列中取出任务并执行之，而其他子线程将继续睡眠在工作队列上。



线程池的一般模型为：

![image-20240408121423601](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20240408121423601.png)






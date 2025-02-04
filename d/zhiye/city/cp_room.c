// Room: /d/city/cp_room.c
// Date: Lsxk 2007/9/25

#include <ansi.h>
inherit ROOM;
#define UPDATE_TIME 10800 //定义每3小时更新一次.
#define DUIJIANG_TIME 3600 //定义对奖时间。 by lsxk@hsbbs 2007/9/26
#define SIZE_OF_SOURCE 20 //定义选择池长度
#define CREDIT_COST 5 //定义用通宝购买的价格。 by lsxk@hsbbs 2007/9/26
#define GOLD_COST 100000 //定义用黄金购买的价格。 by lsxk@hsbbs 2007/9/26

//string *duijiang_char;
//string strPriKaijiang;

//string cp_kaijiang(int);
//#include "buy_caipiao.h";
//#include "duijiang_caipiao.h";

void create()
{
       set("short", HIY"摸彩中心"NOR);
       set("long", @LONG
这里便是扬州城里到处传说的摸彩中心，在这里，有的人一夜
暴富有的人却倾家荡产，沦为街头乞丐。总之，幸运的人称这里为
人间天堂，而另外些人却说这里是人间地狱。
这里竖了一个牌子(sign)，上面似乎写着一些规则。
LONG);

    set("exits", ([
               "east"  :  __DIR__"dating1",
    ]));

    set("item_desc", ([
            "sign": @TEXT

摸彩说明与规则：

规则：
1、系统每次将在26个小写字母，26个大写字母，0~9十个数字以及“~!@#$%^&*”之中随
机选择20个字符作为摸彩后选，并以会以公告形式发送给每个玩家。
2、玩家则需要将这20个字符按照自己的喜好排序，并将其划分为2个字符一对，总共10对
字符组合。
3、系统之后将随机对这20个字符进行自动组合，也将是2个字符一对。
4、摸彩的玩家所选择的10对字符中，任意一对和系统随机排列的一对相一致，则累计中
奖积分。如这个组合是重复中奖组合，则不再累积积分，例如：
系统中奖序号为Aa-12-34-56-78-90-re-yt-iu-po 
某个人购买了:po-po-po-as-fd-er-ge-hr-jh-vb
则“po”组合获得中奖积分，但是只获得1分。第2和第3个“po”不获得中奖积分。
若你中奖的字符对与系统产生的字符对所在的位置一致，则本次获得积分翻倍。
5、系统根据一定算法将你本次的累积积分转化成你购买时的货币。算法如下：
中奖金额 = 购买金额 * 累积积分
(注：累积积分 = 和系统相一致的字符的个数的加全值。例如：本次你总共有4对字符排列
和系统产生的排列相一致，则累积积分为1+2+3+4 =10)
6、购买货币为黄金。

购买方法：
1、使用buy指令，按照如下格式：
buy 你想要的序列号 with 黄金
其中，序列号输入必须由20个字符组成，并且每2个字符需要用"-"符号连接。例如：
buy 12-34-56-78-90-09-87-65-43-21 with 黄金
2、系统不会检查你输入的序号是否从规定的20个字符里选择的，只会判断你输入的字符长
度是否满足要求。即，你输入了29个字符，系统就认为你输入正确。
3、系统产生的中奖字符100%是在一开始公告中的20个字符里产生的，且不会重复。
4、每次购买，系统自动在你的银行里扣除100锭黄金作为购买费用，而不使用你身上的黄金。
5、每人每期购买的数量不限制。你可以购买多个排列组合。
6、购买后，系统会给你一张“彩票联”，彩票联在你下线再上线时，依旧存在你的身上。
7、丢弃“彩票联”即算放弃这次对奖机会，也就浪费了你购买的钱。
8、系统每3小时产生一次备选号码，产生备选号码后的2小时内，都可以自由购买彩票。
产生备选序号后的第3个小时准时开奖，并公布中奖序号，请玩家去摸彩中心对奖。
9、系统每产生一次新的被选号码的同时，即宣告前一次的摸彩过期，无法再进行对奖。
10、对奖指令：duijiang   每使用一次，对奖一组购买的序列号。

查询方法：
在摸彩中心使用chakan指令，可以显示当前被选号码，如果已经处于对奖阶段，则还会显
示中奖排列序号。

TEXT
    ]) );
       set("indoors", "摸彩中心" );
       set("no_fight",1);
       set("no_sleep",1);

   setup();

  //  remove_call_out("update_source");
  //  remove_call_out("update_kaijiang");
  //  call_out("update_source",UPDATE_TIME);
  //  call_out("update_kaijiang",(UPDATE_TIME-DUIJIANG_TIME));
}

void init()
{
  //  add_action("do_chakan", "chakan");
  //  add_action("buy_caipiao","buy");
  //  add_action("do_duijiang","duijiang");
/*
    if(wizardp(this_player()) && this_player()->query("id")=="lsxk")
        add_action("do_zuobi","zuobi");
*/

}
/*

void do_zuobi(string arg)
{
    //object me = this_player();

    set("zuobi",arg);
    duijiang_char = explode(arg, "-");

    return;
}

void update_source()
{
    This_Source = Random_Source(SIZE_OF_SOURCE);
    remove_call_out("update_source");
    call_out("update_source",UPDATE_TIME);
}

void update_kaijiang()
{
    string kj_result;

    set("no_buy",1);//对奖时间，无法购买彩票. by lsxk@hsbbs 2007/9/26

    if(!query("zuobi")){
        delete("zuobi");
        kj_result = cp_kaijiang(0);
    }
    else kj_result = query("zuobi");
    message("system",HIY"\n\n【书剑搏彩】："+HIW+"本期书剑开彩序号为："+HIR+kj_result+HIW+" ，请中奖者在一小时之内前去摸彩中心对奖，过期不候！\n\n"NOR, users());

    //删除备份记录。by lsxk@hsbbs 2007/9/28
    rm("/log/cpTag.c");

    remove_call_out("update_kaijiang");
    call_out("update_kaijiang",UPDATE_TIME);
}

int do_chakan(object me)
{
 //   string strResult;
    string strPriKaijiang;
    me = this_player();

    tell_object(me,HIY"本次的开彩选择号码为：\n"+HIR+This_Source+"\n"NOR);

    if(query("no_buy")){
        tell_object(me,HIC"本次的摸彩中奖排列号码为：\n"+HIW+strPriKaijiang+"\n"NOR);
    }
    return 1;
}

private string cp_kaijiang(int tag)
{
    string *strTemp, *strTemp2, strLast, strResult, p;
    int i, j, k;

    //将字符串分解成单个字符存储到strTemp2数组中。 by lsxk@hsbbs 2007/9/25
    strLast = This_Source;
    for(i=0;i<SIZE_OF_SOURCE;i++){
        sscanf(strLast, "%s %s",p,strLast);
        if(!strTemp2) strTemp2 = ({p});
        else if((i+1)<SIZE_OF_SOURCE) strTemp2 += ({p});
        else strTemp2 += ({strLast});
    }

    //将字符串随机排列存储到strTemp数组中。 by lsxk@hsbbs 2007/9/25
    for(i=0;i<SIZE_OF_SOURCE;i++){
        p = strTemp2[random(sizeof(strTemp2))];
        if(!strTemp) strTemp = ({p});
        else strTemp += ({p});
        strTemp2 -= ({p});
    }

    if(tag==0)
    duijiang_char = strTemp;

    //将strTemp中的数组按照XX-XX-XX-XX的格式输出。by lsxk@hsbbs 2007/9/25
    j = sizeof(strTemp);
    for(k=0;k<j;k++){
        if(!strResult)
            strResult = strTemp[k];
        else if((k)%2==0)
            strResult = strResult+"-"+strTemp[k];
        else
            strResult = strResult+strTemp[k];
    }
    if(tag==0)
    strPriKaijiang = strResult;

    return strResult;
}
*/


#include <ansi.h>
#define Weapon_LEVEL            100
#define SKILLS_LEVEL            551

#define KNOWLEDGE_LEVEL         350

#define GIVE_EXP                17900000

#define MAX_NEILI               34000

#define MAX_JINGLI              7000

inherit NPC;
string ask_newbie();
string ask_fanhui();
string ask_xingxiu();
string ask_sld();
string ask_wudang();
string ask_ss();
string ask_emei();
string ask_shaolin();
string ask_xs();
string ask_mingjiao();
string ask_kl();
string ask_hs();
string ask_gb();
string ask_riyue();
string ask_baixing();
string ask_mur();
string ask_tttt();
string ask_xuedao();
string ask_thd();
string ask_tz();
string ask_tls();
string ask_ljg();
string ask_quanzhen();
object ob = this_object();

void create()
{
    set_name(HIR"书剑礼物使者(终极)"NOR, ({ "shizhee" }));
    set("long", HIW"你可以ask shizhe about newbie,在ask shizhe about 拜师,喜欢哪个门派就ask shizhe about ***(门派),addoil all \n"NOR);
    set("gender", "男性");
    set("age", 70);
    set("per", 24);
    set("str", 40);
    set("int", 40);
    set("con", 40);
    set("dex", 40);
    set("qi",5000);
    set("jingli",6000);
    set("max_qi", 8000);
    set("max_jing", 5000);
    set("eff_jingli", 6000);
    set("jiali", 190);
    set("combat_exp", 9000000);
    set("shen", 25000);
    set("chat_chance_combat", 60);
    set("chat_msg_combat", ({
(: exert_function, "taiji" :),
(: perform_action, "sword.chan" :),
(: perform_action, "cuff.zhen" :),
(: perform_action, "cuff.zhan" :),
(: perform_action, "cuff.ji" :)
      }));
    setup();
    set("inquiry", ([
        "newbie" : (: ask_newbie :),
		 "反悔" : (: ask_fanhui :),
        "拜师" : "你要拜哪里？（ask shizhe about 〈门派名称〉）\n武当？少林？全真教？星宿？日月神教？灵鹫宫？华山？丐帮？神龙岛？昆仑？铁掌？\n古墓？慕容？桃花岛？天龙寺？大轮寺？嵩山？明教？峨嵋?\n如果有 ask 后没有反应的，那么就是那个门派已经关闭了。\n",
        "大轮寺" : (: ask_xs :),
        "桃花岛" : (: ask_thd :),
        "星宿" : (: ask_xingxiu :),
        "武当" : (: ask_wudang :),
        "峨嵋" : (: ask_emei :),
        "明教" : (: ask_mingjiao :),
        "少林" : (: ask_shaolin :),
	    "血刀门" : (: ask_xuedao :),
		"日月神教" : (: ask_riyue :),
        "丐帮" : (: ask_gb :),
        "古墓" : (: ask_tttt :),
        "华山" : (: ask_hs :),
		"全真教" : (: ask_quanzhen :),
        "嵩山" : (: ask_ss :),
        "慕容" : (: ask_mur :),
        "天龙寺" : (: ask_tls :),
        "铁掌" : (: ask_tz :),
        "神龙岛" : (: ask_sld :),
		"灵鹫宫" : (: ask_ljg :),
		"百姓" : (: ask_baixing :),
        "昆仑" : (: ask_kl :),
      ]) );
}

string ask_newbie()
{ 
    mapping skill;
    string *skl;
    int i;
    object letter;
    object me = this_object();
    object ob = this_player();
    write ("请输入 ask shizhe about 拜师 来要技能。\n");
    ob->set_skill("dodge",1);
    skill = ob->query_skills();
    skl = keys(skill);
    i = sizeof(skl);
    while (i--) 
    {
      ob->delete_skill(skl[i]);              
    }
    message_vision(HIC"书剑礼物使者废去了你的所有武功！\n"NOR,me,ob);
    message_vision(HIW"另外赠送你一年的贵宾服务时间！\n"NOR,me,ob);
    ob->delete("double_attack");
    this_player()->set_skill("dodge",SKILLS_LEVEL);
    this_player()->set_skill("force",SKILLS_LEVEL);
    this_player()->set_skill("parry",SKILLS_LEVEL);
    this_player()->set_skill("duanzao",Weapon_LEVEL);
    this_player()->set_skill("zhizao",Weapon_LEVEL);
    this_player()->set_skill("literate",ob->query("int") * 10);
    this_player()->set_skill("medicine",122);

    this_player()->set("balance",2000000);

	ob->set("neili",MAX_NEILI);
    ob->set("max_jing",MAX_NEILI);
    ob->set("jing",MAX_NEILI);
    ob->set("qi",MAX_NEILI);
    ob->set("max_qi",MAX_NEILI);
    ob->set("max_neili",MAX_NEILI);
    ob->set("jingli",MAX_JINGLI);
    ob->set("max_jingli",MAX_NEILI);
    ob->set("eff_jingli",MAX_NEILI);
    ob->reincarnate();
    ob->set("kar",20+random(10));
	ob->set("SJ_Credit",1000);
	ob->set("pur",10+random(20));
	ob->set("per",25+random(5));

  
	ob->set("str",20);

	ob->set("con",20);
	ob->set("dex",20);

	ob->set("int",20);

	ob->set("combat_exp",GIVE_EXP);
    ob->set("job_time/丐帮",400);
    ob->set("shizhe_newbie",1);
    ob->set("registered", 3);    
    ob->set("vip/vip_time",time());
    ob->add("vip/vip_time",365*24*3600);
	ob->set("vip/vip_start_time",time());    
    ob->set("age",35);
    ob->set("mud_age",1000000);
    ob->set("enter_wuguan",0);
    if(objectp(letter = new(__DIR__"obj/letter")))
        {        
        command("say 我这里还有一封锻造推荐信，你这就拿去吧，够照顾你的了吧！");
        letter->move(ob);
        message_vision(""HIW"书剑礼物使者"NOR"给你一封「"+letter->query("name")+"」。\n",me,  this_object());   
        return "如果你不解冶铁煅造之术，可以使用 help dazao 获得详细信息。"; 
        }
    return "为鼓励newbie特此奖励!请用 ask shizhe about 拜师 来要技能。\n"; 
}
string ask_fanhui()
{
    mapping skill;
    string *skl;
    int i;
    object me = this_object();
    object ob = this_player();
    skill = ob->query_skills();
    skl = keys(skill);
    i = sizeof(skl);
    while (i--) 
    {
      ob->delete_skill(skl[i]);              
    }
    message_vision(HIC"书剑礼物使者废去了你的所有武功！\n"NOR,me,ob);
    ob->delete("shizhe_newbie");
    ob->delete("shizhe_拜师");
    ob->delete("mishu_newbie");
    ob->delete("mishu_want");
    ob->set("family",0);
    return "请重新ask shizhe about newbie一次。\n";
}

string ask_riyue()
{
    if (this_player()->query("shizhe_拜师")) return "你不是要过一次门派skills了嘛！？\n";
    if (!this_player()->query("shizhe_newbie")) return "你必须要先ask shizhe about newbie！？\n";
    message_vision(HIY "使者"+ NOR "一挥手，一阵狂风将$N吹得无影无踪了。"+ NOR "\n",this_player());
    this_object()->create_family("日月神教", 10, "弟子");
    this_object()->recruit_apprentice(this_player());
    this_object()->delete("title");
    //this_player()->move("/d/xingxiu/xxh");
    this_player()->set("job_time/星宿",5000);
    this_player()->set_skill("tianmo-gong",SKILLS_LEVEL);
	this_player()->set_skill("xixing-dafa",SKILLS_LEVEL);
	this_player()->set_skill("force",SKILLS_LEVEL);
	this_player()->set_skill("dodge",SKILLS_LEVEL);
	this_player()->set_skill("parry",SKILLS_LEVEL);
	this_player()->set_skill("blade",SKILLS_LEVEL);
	this_player()->set_skill("tianmo-dao",SKILLS_LEVEL);
    this_player()->set_skill("tianmo-zhang",SKILLS_LEVEL);
    this_player()->set_skill("huanmo-wubu",SKILLS_LEVEL);
    this_player()->set_skill("tianmo-jue",SKILLS_LEVEL);
    this_player()->set_skill("tianmo-gun",SKILLS_LEVEL);
    this_player()->set_skill("club",SKILLS_LEVEL);
	this_player()->set_skill("dali-shenmofu",SKILLS_LEVEL);
    this_player()->set_skill("axe",SKILLS_LEVEL);
	this_player()->set_skill("throwing",SKILLS_LEVEL);
    this_player()->set_skill("mantian-huayu",SKILLS_LEVEL);
	this_player()->set_skill("strike",SKILLS_LEVEL);
    this_player()->set_skill("sword",SKILLS_LEVEL);
    this_player()->set_skill("qixian-wuxingjian",SKILLS_LEVEL);
    this_player()->set_skill("poison",150);
    this_player()->set("shizhe_拜师",1);
    this_player()->set("shen",-100000);
    this_player()->set("hmy/quest/tmgf",1);
	
    return "hehe";
}

string ask_xingxiu()
{
    if (this_player()->query("shizhe_拜师")) return "你不是要过一次门派skills了嘛！？\n";
    if (!this_player()->query("shizhe_newbie")) return "你必须要先ask shizhe about newbie！？\n";
    message_vision(HIY "使者"+ NOR "一挥手，一阵狂风将$N吹得无影无踪了。"+ NOR "\n",this_player());
    this_object()->create_family("星宿派", 2, "弟子");
    this_object()->recruit_apprentice(this_player());
    this_object()->delete("title");
    this_player()->move("/d/xingxiu/xxh");
    this_player()->set("job_time/星宿",5000);
    this_player()->set_skill("huagong-dafa",SKILLS_LEVEL);
	this_player()->set_skill("force",SKILLS_LEVEL);
	this_player()->set_skill("dodge",SKILLS_LEVEL);
	this_player()->set_skill("parry",SKILLS_LEVEL);
	this_player()->set_skill("hook",SKILLS_LEVEL);
	this_player()->set_skill("zhuihun-gou",SKILLS_LEVEL);
    this_player()->set_skill("chousui-zhang",SKILLS_LEVEL);
    this_player()->set_skill("sanyin-zhua",SKILLS_LEVEL);
    this_player()->set_skill("zhaixingshu",SKILLS_LEVEL);
    this_player()->set_skill("tianshan-zhang",SKILLS_LEVEL);
    this_player()->set_skill("strike",SKILLS_LEVEL);
    this_player()->set_skill("staff",SKILLS_LEVEL);
    this_player()->set_skill("claw",SKILLS_LEVEL);
    this_player()->set_skill("poison",200);
    this_player()->set("shizhe_拜师",1);
    this_player()->set("shen",-100000);
    return "hehe";
}
string ask_ljg()
{
    if (this_player()->query("shizhe_拜师")) return "你不是要过一次门派skills了嘛！？\n";
    if (!this_player()->query("shizhe_newbie")) return "你必须要先ask shizhe about newbie！？\n";
    message_vision(HIY "使者"+ NOR "一挥手，一阵狂风将$N吹得无影无踪了。"+ NOR "\n",this_player());
    this_object()->create_family("灵鹫宫", 3, "弟子");
    this_object()->recruit_apprentice(this_player());
    this_object()->delete("title");
    //this_player()->move("/d/xingxiu/xxh");
   // this_player()->set("job_time/星宿",5000);
    this_player()->set_skill("bahuang-gong",SKILLS_LEVEL);
	this_player()->set_skill("force",SKILLS_LEVEL);
	this_player()->set_skill("dodge",SKILLS_LEVEL);
	this_player()->set_skill("parry",SKILLS_LEVEL);
	this_player()->set_skill("hand",SKILLS_LEVEL);
	this_player()->set_skill("strike",SKILLS_LEVEL);
    this_player()->set_skill("liuyang-zhang",SKILLS_LEVEL);
    this_player()->set_skill("zhemei-shou",SKILLS_LEVEL);
    this_player()->set_skill("yueying-wubu",SKILLS_LEVEL);
    this_player()->set_skill("sword",SKILLS_LEVEL);
    this_player()->set_skill("tianyu-qijian",SKILLS_LEVEL);
    this_player()->set_skill("blade",SKILLS_LEVEL);
    this_player()->set_skill("ruyi-dao",SKILLS_LEVEL);
    this_player()->set_skill("art",200);
    this_player()->set("shizhe_拜师",1);
    this_player()->set("shen",0);
    this_player()->set("quest/tonglao/pass",1);
    return "hehe";
}
string ask_xuedao()
{
    if (this_player()->query("shizhe_拜师")) return "你不是要过一次门派skills了嘛！？\n";
    if (!this_player()->query("shizhe_newbie")) return "你必须要先ask shizhe about newbie！？\n";
    message_vision(HIY "使者"+ NOR "一挥手，一阵狂风将$N吹得无影无踪了。"+ NOR "\n",this_player());
    this_object()->create_family("血刀门", 3, "弟子");
    this_object()->recruit_apprentice(this_player());
    this_object()->delete("title");
    this_player()->move("/d/xingxiu/xxh");
     this_player()->set("job_time/雪山",5000);
    this_player()->set_skill("xuedao-dafa",SKILLS_LEVEL);
	this_player()->set_skill("force",SKILLS_LEVEL);
	this_player()->set_skill("dodge",SKILLS_LEVEL);
	this_player()->set_skill("parry",SKILLS_LEVEL);
	this_player()->set_skill("blade",SKILLS_LEVEL);
	this_player()->set_skill("claw",SKILLS_LEVEL);
    this_player()->set_skill("tianwang-zhua",SKILLS_LEVEL);
    this_player()->set_skill("sword",SKILLS_LEVEL);
    this_player()->set_skill("mingwang-jian",SKILLS_LEVEL);
    this_player()->set_skill("xuedao-jing",SKILLS_LEVEL);
    this_player()->set_skill("poison",200);
    this_player()->set("shizhe_拜师",1);
    this_player()->set("shen",-100000);
    return "hehe";
}
string ask_ss()
{
    if (this_player()->query("shizhe_拜师")) return "你不是要过一次门派skills了嘛！？\n";
    if (!this_player()->query("shizhe_newbie")) return "你必须要先ask shizhe about newbie！？\n";
    message_vision(HIY "使者"+ NOR "一挥手，一阵狂风将$N吹得无影无踪了。"+ NOR "\n",this_player());
    this_object()->create_family("嵩山派", 4, "弟子");
    this_object()->recruit_apprentice(this_player());
    this_object()->delete("title");
    this_player()->move("/d/songshan/damen");
    this_player()->set_skill("songyang-zhang",SKILLS_LEVEL);
    this_player()->set_skill("strike",SKILLS_LEVEL);
    this_player()->set_skill("songyang-shou",SKILLS_LEVEL);
    this_player()->set_skill("hand",SKILLS_LEVEL);
    this_player()->set_skill("songshan-jian",SKILLS_LEVEL);
    this_player()->set_skill("hanbing-shenzhang",SKILLS_LEVEL);
    this_player()->set_skill("sword",SKILLS_LEVEL);
    this_player()->set_skill("hanbing-zhenqi",SKILLS_LEVEL);
    this_player()->set_skill("force",SKILLS_LEVEL);
    this_player()->set_skill("zhongyuefeng",SKILLS_LEVEL);
    this_player()->set_skill("dodge",SKILLS_LEVEL);
    this_player()->set_skill("parry",SKILLS_LEVEL);
    this_player()->set("shen",-100000);
    this_player()->set("job_time/嵩山",5000);
    this_player()->set("songshan_points",6000);
	this_player()->set("quest/ss/ssjf/jueji/pass",1);
	this_player()->set("quest/ss/hbzq/pass",1);

    this_player()->set("shizhe_拜师",1);
    return "hehe";
}

string ask_wudang()
{
    if (this_player()->query("shizhe_拜师")) return "你不是要过一次门派skills了嘛！？\n";
    if (!this_player()->query("shizhe_newbie")) return "你必须要先ask shizhe about newbie！？\n";
    message_vision(HIY "使者"+ NOR "一挥手，一阵狂风将$N吹得无影无踪了。"+ NOR "\n",this_player());
    this_object()->create_family("武当派", 5, "弟子");
    this_object()->recruit_apprentice(this_player());
    this_object()->delete("title");
    //this_player()->move("/d/wudang/houyuan");
    this_player()->set_skill("taiji-quan",SKILLS_LEVEL);
    this_player()->set_skill("strike",SKILLS_LEVEL);
    this_player()->set_skill("taiji-jian",SKILLS_LEVEL);
    this_player()->set_skill("taoism",200);
    this_player()->set_skill("tiyunzong",SKILLS_LEVEL);
	this_player()->set_skill("juehu-shou",SKILLS_LEVEL);
	this_player()->set_skill("yitian-tulong",SKILLS_LEVEL);
	this_player()->set_skill("juehu-shou",SKILLS_LEVEL);
	this_player()->set_skill("hand",SKILLS_LEVEL);
    this_player()->set_skill("yinyun-ziqi",SKILLS_LEVEL);
    this_player()->set_skill("sword",SKILLS_LEVEL);
    this_player()->set_skill("zhenshan-mianzhang",SKILLS_LEVEL);
	this_player()->set_skill("yitian-tulong",SKILLS_LEVEL);
	this_player()->set_skill("brush",SKILLS_LEVEL);
    this_player()->set_skill("cuff",SKILLS_LEVEL);
    this_player()->set_skill("blade",SKILLS_LEVEL);
	this_player()->set_skill("xuanxu-daofa",SKILLS_LEVEL);
    this_player()->set("shen",100000);
	this_player()->set("quest/tjq/taiji","pass");
	this_player()->set("quest/wd/tjj/qianjin/pass",1);
	this_player()->set("quest/wd/yyzq/taiji/pass",1);
	this_player()->set("quest/wd/tjj/sanhuan/pass",1);
    this_player()->set("shizhe_拜师",1);
    return "hehe";
}
string ask_emei()
{
    object ob;
    ob=this_player();
    if (ob->query("shizhe_拜师")) return "你不是要过一次门派skills了嘛！？\n";
   if (!this_player()->query("shizhe_newbie")) return "你必须要先ask shizhe about newbie！？\n";
    message_vision(HIY "使者"+ NOR "一挥手，一阵狂风将$N吹得无影无踪了。"+ NOR "\n",this_player());
    this_object()->create_family("峨嵋派", 5, "弟子");
    this_object()->recruit_apprentice(this_player());
    this_object()->delete("title");
    //this_player()->move("/d/emei/houdian");
    this_player()->set_skill("anying-fuxiang",SKILLS_LEVEL);
    this_player()->set_skill("blade",SKILLS_LEVEL);
    this_player()->set_skill("yanxing-daofa",SKILLS_LEVEL);
    this_player()->set_skill("dacheng-fofa",200);
    this_player()->set_skill("dodge",SKILLS_LEVEL);
    this_player()->set_skill("force",SKILLS_LEVEL);
    this_player()->set_skill("hand",SKILLS_LEVEL);
    this_player()->set_skill("huifeng-jian",SKILLS_LEVEL);
    this_player()->set_skill("jieshou-jiushi",SKILLS_LEVEL);
	this_player()->set_skill("strike",SKILLS_LEVEL);
	this_player()->set_skill("sixiang-zhang",SKILLS_LEVEL);
    this_player()->set_skill("linji-jianzhen",200);
	this_player()->set_skill("jiuyin-zhengong",180);
	this_player()->set_skill("yinlong-bian",SKILLS_LEVEL);
	this_player()->set_skill("whip",SKILLS_LEVEL);
	this_player()->set_skill("claw",SKILLS_LEVEL);
	this_player()->set_skill("jiuyin-baiguzhua",SKILLS_LEVEL);

    this_player()->set_skill("sixiang-zhang",SKILLS_LEVEL);
    this_player()->set_skill("parry",SKILLS_LEVEL);
    this_player()->set_skill("linji-zhuang",SKILLS_LEVEL);
    this_player()->set_skill("strike",SKILLS_LEVEL);
    this_player()->set_skill("sword",SKILLS_LEVEL);
    this_player()->set("shizhe_拜师",1);
	this_player()->set("em/mie/pass",1);
	this_player()->set("em/jue/pass",1);
	this_player()->set("quest/emei/hfjf/liaoyuan/pass",1);
	this_player()->set("emjy/pass",1);
    return "hehe";
}
string ask_shaolin()
{
object ob;
ob=this_player();
if (ob->query("shizhe_拜师")) return "你不是要过一次门派skills了嘛！？\n";
   if (!ob->query("shizhe_newbie")) return "你必须要先ask shizhe about newbie！？\n";
if((string)ob->query("gender") == "女性" )
return "少林寺武功需要纯阳之体，小姑娘可不收啊! ";
message_vision(HIY "使者"+ NOR "一挥手，一阵狂风将$N吹得无影无踪了。"+ NOR "\n",this_player());
this_object()->create_family("少林派", 99, "弟子");
this_object()->recruit_apprentice(this_player());
this_object()->delete("title");       
this_player()->move("/d/shaolin/smdian");
this_player()->set_skill("buddhism",200);
this_player()->set_skill("jingang-quan",SKILLS_LEVEL);//6高级
this_player()->set_skill("cuff",SKILLS_LEVEL);
this_player()->set_skill("banruo-zhang",SKILLS_LEVEL);
this_player()->set_skill("strike",SKILLS_LEVEL);
this_player()->set_skill("yizhi-chan",SKILLS_LEVEL);
this_player()->set_skill("finger",SKILLS_LEVEL);
this_player()->set_skill("longzhua-gong",SKILLS_LEVEL);
this_player()->set_skill("claw",SKILLS_LEVEL);
this_player()->set_skill("qianye-shou",SKILLS_LEVEL);
this_player()->set_skill("hand",SKILLS_LEVEL);
this_player()->set_skill("ruying-suixingtui",SKILLS_LEVEL);
this_player()->set_skill("leg",SKILLS_LEVEL);
this_player()->set_skill("riyue-bian",SKILLS_LEVEL);
this_player()->set_skill("ranmu-daofa",SKILLS_LEVEL);
this_player()->set_skill("weituo-chu",SKILLS_LEVEL);
        //3 weapon 但是不给三大武学只给基本自己选择
this_player()->set_skill("blade",SKILLS_LEVEL);
this_player()->set_skill("club",SKILLS_LEVEL);
this_player()->set_skill("whip",SKILLS_LEVEL);
this_player()->set_skill("yijin-jing",SKILLS_LEVEL);
this_player()->set_skill("shaolin-shenfa",SKILLS_LEVEL);

    this_player()->set("shen",100000);
    this_player()->set("shizhe_拜师",1);
    return "hehe";
}
string ask_mingjiao()
{
    if (this_player()->query("shizhe_拜师")) return "你不是要过一次门派skills了嘛！？\n";
   if (!this_player()->query("shizhe_newbie")) return "你必须要先ask shizhe about newbie！？\n";
    message_vision(HIY "使者"+ NOR "一挥手，一阵狂风将$N吹得无影无踪了。"+ NOR "\n",this_player());
    this_object()->create_family("明教", 37, "弟子");
    this_object()->recruit_apprentice(this_player());
    this_object()->delete("title");
    this_player()->move("/d/mingjiao/jyt");
    this_player()->set_skill("qishang-quan",SKILLS_LEVEL);
	this_player()->set_skill("huanyin-zhi",SKILLS_LEVEL);
	this_player()->set_skill("finger",SKILLS_LEVEL);
	this_player()->set_skill("duoming-jinhua",SKILLS_LEVEL);
	this_player()->set_skill("throwing",SKILLS_LEVEL);
    this_player()->set_skill("cuff",SKILLS_LEVEL);
    this_player()->set_skill("hanbing-mianzhang",SKILLS_LEVEL);
    this_player()->set_skill("strike",SKILLS_LEVEL);
    this_player()->set_skill("yingzhua-shou",SKILLS_LEVEL);
	this_player()->set_skill("jiuyang-shengong",SKILLS_LEVEL);
    this_player()->set_skill("hand",SKILLS_LEVEL);
    this_player()->set_skill("shenghuo-lingfa",SKILLS_LEVEL);
    this_player()->set_skill("dagger",SKILLS_LEVEL);
    this_player()->set_skill("liehuo-jian",SKILLS_LEVEL);
    this_player()->set_skill("sword",SKILLS_LEVEL);
    this_player()->set_skill("lieyan-dao",SKILLS_LEVEL);
    this_player()->set_skill("blade",SKILLS_LEVEL);
    this_player()->set_skill("shenghuo-fumozhen",200);
    this_player()->set_skill("qiankun-danuoyi",SKILLS_LEVEL);
    this_player()->set_skill("shenghuo-shengong",SKILLS_LEVEL);
    this_player()->set_skill("piaoyi-shenfa",SKILLS_LEVEL);
    this_player()->set("shen",100000);
	this_player()->set("mjqkdny/pass",1);
	this_player()->set("mj/jiuyang/pass",3);
	this_player()->set("mjyzs/pass",1);
	this_player()->set("quest/mj/shlf/givezhang",1);
    this_player()->set("shizhe_拜师",1);
    return "hehe";
}

string ask_gb()
{
    if (this_player()->query("shizhe_拜师")) return "你不是要过一次门派skills了嘛！？\n";
    if (!this_player()->query("shizhe_newbie")) return "你必须要先ask shizhe about newbie！？\n";
    message_vision(HIY "使者"+ NOR "一挥手，一阵狂风将$N吹得无影无踪了。"+ NOR "\n",this_player());
    this_object()->create_family("丐帮", 99, "弟子");
    this_object()->recruit_apprentice(this_player());
    this_object()->delete("title");        
  //  this_player()->move("/d/gb/pomiao");
    this_player()->set_skill("xianglong-zhang",SKILLS_LEVEL);
    this_player()->set_skill("lianhua-zhang",SKILLS_LEVEL);
    this_player()->set_skill("strike",SKILLS_LEVEL);
    this_player()->set_skill("fengmo-zhang",SKILLS_LEVEL);
    this_player()->set_skill("staff",SKILLS_LEVEL);
    this_player()->set_skill("huifeng-bian",SKILLS_LEVEL);
    this_player()->set_skill("whip",SKILLS_LEVEL);
    this_player()->set_skill("suohou-shou",SKILLS_LEVEL);
    this_player()->set_skill("hand",SKILLS_LEVEL);
    this_player()->set_skill("dagou-bang",SKILLS_LEVEL);
    this_player()->set_skill("stick",SKILLS_LEVEL);
    this_player()->set_skill("liuhe-daofa",SKILLS_LEVEL);
    this_player()->set_skill("blade",SKILLS_LEVEL);
    this_player()->set_skill("huntian-qigong",SKILLS_LEVEL);
    this_player()->set_skill("xiaoyaoyou",SKILLS_LEVEL);
    this_player()->set_skill("begging",200);
    this_player()->set_skill("bangjue",200);
    this_player()->set_skill("dagou-zhen",200);
    this_player()->set_skill("checking",200);
    this_player()->set_skill("stealing",200);
    this_player()->set_skill("begging",200);
    this_player()->set("shen",600000);
    this_player()->set("job_time/抓蛇",1000);
    this_player()->set("job_time/丐帮",1000);
    this_player()->set("job_time/刺杀",1000);
    this_player()->set("job_time/颂摩崖",1000);
    this_player()->set("gb/gift", 1);
    this_player()->set("xlz/hang", 1);
// 删除特殊quest 记号
    this_player()->set("dgb/wugou",1);
    this_player()->set("xlz/hang",1);
	this_player()->set("kanglong/pass",1);
    this_player()->set("xlz/sanzhao","pass");
    this_player()->set("shizhe_拜师",1);
    return "hehe";
}

string ask_hs()
{
    if (this_player()->query("shizhe_拜师")) return "你不是要过一次门派skills了嘛！？\n";
    if (!this_player()->query("shizhe_newbie")) return "你必须要先ask shizhe about newbie！？\n";
    message_vision(HIY "使者"+ NOR "一挥手，一阵狂风将$N吹得无影无踪了。"+ NOR "\n",this_player());
    this_object()->create_family("华山派", 99, "弟子");
    this_object()->recruit_apprentice(this_player());
    this_object()->delete("title");
    //this_player()->move("/d/huashan/zhengqi");
    this_player()->set_skill("huashan-shenfa",SKILLS_LEVEL);
    this_player()->set_skill("claw",SKILLS_LEVEL);
	this_player()->set_skill("dugu-jiujian",SKILLS_LEVEL);
    this_player()->set_skill("huashan-jianfa",SKILLS_LEVEL);
    this_player()->set_skill("cuff",SKILLS_LEVEL);
    this_player()->set_skill("dodge",SKILLS_LEVEL);
    this_player()->set_skill("force",SKILLS_LEVEL);
    this_player()->set_skill("zixia-gong",SKILLS_LEVEL);
    this_player()->set_skill("blade",SKILLS_LEVEL);
    this_player()->set_skill("poyu-quan",SKILLS_LEVEL);
    this_player()->set_skill("parry",SKILLS_LEVEL);
    this_player()->set_skill("sword",SKILLS_LEVEL);
    this_player()->set_skill("hunyuan-zhang",SKILLS_LEVEL);
    this_player()->set_skill("strike",SKILLS_LEVEL);
    this_player()->set_skill("huashan-qigong",SKILLS_LEVEL);
    this_player()->set_skill("zhengqi-jue",200);
	this_player()->set_skill("ziyin-yin",200);
    this_player()->set("shen",100000);
    this_player()->set("job_time/丐帮",1000);
    this_player()->set("shizhe_拜师",1);
	this_player()->set("quest/zixia/pass",1);
	this_player()->set("quest/hs/hssb/pass",1);
	this_player()->set("quest/hs/hsjf/jiejian/pass",1);
	this_player()->set("quest/hs/dgjj/wuzhao/pass",1);
	this_player()->set("quest/hs/dgjj/jiushi/pass",1);
	this_player()->set("int",50);
    return "hehe";
}
string ask_tttt()
{
//object suo
    if (this_player()->query("shizhe_拜师")) return "你不是要过一次门派skills了嘛！？\n";
    if (!this_player()->query("shizhe_newbie")) return "你必须要先ask shizhe about newbie！？\n";
    if (this_player()->query("per") < 25){
		this_player()->set("per",30);
     return "你天生容貌欠佳, 恐怕今生难圆双剑合壁之美梦。\n";
	}
    message_vision(HIY "使者"+ NOR "一挥手，一阵狂风将$N吹得无影无踪了。"+ NOR "\n",this_player());
    this_object()->create_family("古墓派", 99, "弟子");
    this_object()->recruit_apprentice(this_player());
    this_object()->delete("title");
   //  this_player()->move("/d/gumu/jqg/wshi");
//鉴于GM 都是帅哥靓妹
    this_player()->set_skill("strike",SKILLS_LEVEL);    
    this_player()->set_skill("sword",SKILLS_LEVEL);
    this_player()->set_skill("hand",SKILLS_LEVEL);
    this_player()->set_skill("whip",SKILLS_LEVEL);    
    this_player()->set_skill("cuff",SKILLS_LEVEL);            
    this_player()->set_skill("yunu-xinjing",SKILLS_LEVEL);
	//this_player()->set_skill("anran-zhang",SKILLS_LEVEL);
	this_player()->set_skill("wudu-shenzhang",SKILLS_LEVEL);

    this_player()->set_skill("yunu-shenfa",SKILLS_LEVEL);
    this_player()->set_skill("yunu-jianfa",SKILLS_LEVEL);
   // this_player()->set_skill("xuantie-jianfa",SKILLS_LEVEL);
    this_player()->set_skill("meinu-quanfa",SKILLS_LEVEL);
    this_player()->set_skill("quanzhen-jianfa",SKILLS_LEVEL);
    this_player()->set_skill("yinsuo-jinling",SKILLS_LEVEL);
    this_player()->set_skill("tianluo-diwang",SKILLS_LEVEL);
	this_player()->set_skill("jiuyin-zhengong",220);
	this_player()->set_skill("yinlong-bian",SKILLS_LEVEL);
	this_player()->set_skill("claw",SKILLS_LEVEL);
	this_player()->set_skill("jiuyin-baiguzhua",SKILLS_LEVEL);
	this_player()->set_skill("daode-jing",220);
	this_player()->set_skill("jiuyin-shenzhua",SKILLS_LEVEL);
	this_player()->set_skill("jiuyin-shenfa",220);
  /*  if (this_player()->query("gender")!="女性") {
        this_player()->set_skill("tianluo-diwang",SKILLS_LEVEL);
        this_player()->set_skill("quanzhen-jianfa",SKILLS_LEVEL);
        this_player()->set_skill("anran-zhang",SKILLS_LEVEL);
    } else {
        this_player()->set_skill("yunu-jianfa",SKILLS_LEVEL);
        this_player()->set_skill("meinu-quanfa",SKILLS_LEVEL);
		//this_player()->set_skill("meinu-quanfa",SKILLS_LEVEL);
    }*/
    this_player()->set("shen",100000);
    this_player()->set("gmhb","pass");
	this_player()->set("quest/gumu/ynxj/pass",1);
	this_player()->set("quest/jiuyingm/pass",1);
	this_player()->set("quest/gm/ynxj/yufeng/pass",1);
	this_player()->set("quest/gumu/sanwu/pass",1);
	this_player()->set("quest/hubo/pass",1);
	this_player()->set("yueyin",1);
	this_player()->set("quest/gumu/ynjf/mulan/pass",1);
	this_player()->set("quest/gm/dichuan",1);

    this_player()->set("shizhe_拜师",1);
    return "hehe";
}

string ask_mur()
{
    if (this_player()->query("shizhe_拜师")) return "你不是要过一次门派skills了嘛！？\n";
   if (!this_player()->query("shizhe_newbie")) return "你必须要先ask shizhe about newbie！？\n";
    message_vision(HIY "使者"+ NOR "一挥手，一阵狂风将$N吹得无影无踪了。"+ NOR "\n",this_player());
    this_object()->create_family("姑苏慕容", 99, "弟子");
    this_object()->recruit_apprentice(this_player());
    this_object()->delete("title");        
    this_player()->move("/d/mr/yanziwu/yanziwu");
    this_player()->set_skill("blade",SKILLS_LEVEL);
    this_player()->set_skill("murong-daofa",SKILLS_LEVEL);
    this_player()->set_skill("canhe-zhi",SKILLS_LEVEL);
    this_player()->set_skill("douzhuan-xingyi",SKILLS_LEVEL);
    this_player()->set_skill("finger",SKILLS_LEVEL);
    this_player()->set_skill("murong-jianfa",SKILLS_LEVEL);
    this_player()->set_skill("shenyuan-gong",SKILLS_LEVEL);
    this_player()->set_skill("strike",SKILLS_LEVEL);
    this_player()->set_skill("sword",SKILLS_LEVEL);
    this_player()->set_skill("xingyi-zhang",SKILLS_LEVEL);
    this_player()->set_skill("yanling-shenfa",SKILLS_LEVEL);
   // this_player()->set("quest/",SKILLS_LEVEL);
    this_player()->set("shenyuan/powerup", 1);
	this_player()->set("canhe/pass", 1);
    this_player()->set("shizhe_拜师",1);
    return "hehe";
}
string ask_thd()
{
    if (this_player()->query("shizhe_拜师")) return "你不是要过一次门派skills了嘛！？\n";
   if (!this_player()->query("shizhe_newbie")) return "你必须要先ask shizhe about newbie！？\n";
    message_vision(HIY "使者"+ NOR "一挥手，一阵狂风将$N吹得无影无踪了。"+ NOR "\n",this_player());
    this_object()->create_family("桃花岛", 99, "弟子");
    this_object()->recruit_apprentice(this_player());
    this_object()->delete("title");   
    //this_player()->move("/d/thd/jicui");
    this_player()->set("job_time/桃花岛",400);
    this_player()->set_skill("bihai-chaosheng", SKILLS_LEVEL);
    this_player()->set_skill("suibo-zhuliu", SKILLS_LEVEL);
	 this_player()->set_skill("cuixin-zhang", SKILLS_LEVEL);
	 this_player()->set_skill("claw", SKILLS_LEVEL);
	  this_player()->set_skill("jiuyin-baiguzhua", SKILLS_LEVEL);
    this_player()->set_skill("leg", SKILLS_LEVEL);
    this_player()->set_skill("strike", SKILLS_LEVEL);
    this_player()->set_skill("luoying-zhang", SKILLS_LEVEL);
    this_player()->set_skill("hand", SKILLS_LEVEL);
    this_player()->set_skill("finger", SKILLS_LEVEL);
	this_player()->set_skill("lanhua-shou", SKILLS_LEVEL);
    this_player()->set_skill("throwing", SKILLS_LEVEL);
    this_player()->set_skill("tanzhi-shentong", SKILLS_LEVEL);
    this_player()->set_skill("xuanfeng-tui",SKILLS_LEVEL);
    this_player()->set_skill("sword", SKILLS_LEVEL);
    this_player()->set_skill("yuxiao-jian", SKILLS_LEVEL);
    this_player()->set_skill("taoism", 200);
    this_player()->set_skill("qimen-bagua", 200);
    this_player()->set("shizhe_拜师",1);
	this_player()->set("thd/wuji/luoying",1);
	this_player()->set("thd/wuji/yuxiao",1);
    this_player()->set("thd/wuji/kuangfeng",1);
	this_player()->set("thd/wuji/lingxi",1);
	 this_player()->set("thd/wuji/huayu",1);
	this_player()->set("thd/wuji/lhs",1);
    this_player()->set("thd/finish",1);
	this_player()->set("thdjj/ronghe","pass"); 
	message_vision(HIC"请注意，桃花岛只有解开每一门武技的小question，威力才能彻底释放。(灵犀一指。狂风。。。)\n",this_player());
    return "hehe";
}
string ask_tz()
{
 if (!this_player()->query("shizhe_newbie")) return "你必须要先ask shizhe about newbie！？\n";
  if (this_player()->query("shizhe_拜师")) return "你不是要过一次门派skills了嘛！？\n";
    message_vision(HIY "使者"+ NOR "一挥手，一阵狂风将$N吹得无影无踪了。"+ NOR "\n",this_player());
    this_object()->create_family("铁掌帮", 99, "弟子");
    this_object()->recruit_apprentice(this_player());
    this_object()->delete("title");   
    this_player()->move("/d/tiezhang/wztang");
    this_player()->set_skill("guiyuan-tunafa", SKILLS_LEVEL);
    this_player()->set_skill("tiezhang-xinfa", 200);
    this_player()->set_skill("axe", SKILLS_LEVEL);
    this_player()->set_skill("brush", SKILLS_LEVEL);
    this_player()->set_skill("blade", SKILLS_LEVEL);
    this_player()->set_skill("lietian-fu", SKILLS_LEVEL);
    this_player()->set_skill("shuishangpiao", SKILLS_LEVEL);
    this_player()->set_skill("strike", SKILLS_LEVEL);
    this_player()->set_skill("yingou-bifa", SKILLS_LEVEL);
    this_player()->set_skill("liuye-daofa", SKILLS_LEVEL);
    this_player()->set_skill("tiezhang-zhangfa", SKILLS_LEVEL);
    this_player()->set("job_time/铁掌",400);
    this_player()->set("shen",-100000);
    this_player()->set("shizhe_拜师",1);
    this_player()->set("quest/tzauto/over",1);
	this_player()->set("tiezhang/pass",1);
	this_player()->set("quest/tiezhang/piao",1);
	message_vision(HIC"请注意，融合已经开。\n",this_player());
    return "hehe";
}
string ask_sld()
{
    if (this_player()->query("shizhe_拜师")) return "你不是要过一次门派skills了嘛！？\n";
   if (!this_player()->query("shizhe_newbie")) return "你必须要先ask shizhe about newbie！？\n";
    message_vision(HIY "使者"+ NOR "一挥手，一阵狂风将$N吹得无影无踪了。"+ NOR "\n",this_player());
    this_object()->create_family("神龙教", 99, "弟子");
	//this_object()->create_family("神龙教", 99, "弟子");
    this_object()->recruit_apprentice(this_player());
    //this_player()->move("/d/sld/dukou");

    this_player()->set_skill("hook",SKILLS_LEVEL);
    this_player()->set_skill("canglang-goufa",SKILLS_LEVEL);
    this_player()->set_skill("huagu-mianzhang",SKILLS_LEVEL);
    this_player()->set_skill("strike",SKILLS_LEVEL);
    this_player()->set_skill("whip",SKILLS_LEVEL);
    this_player()->set_skill("shenlong-tuifa",SKILLS_LEVEL);
	this_player()->set_skill("hansha-sheying",SKILLS_LEVEL);
    this_player()->set_skill("throwing",SKILLS_LEVEL);

	 this_player()->set_skill("chansi-shou",SKILLS_LEVEL);
    this_player()->set_skill("hand",SKILLS_LEVEL);
    this_player()->set_skill("shenlong-tuifa",SKILLS_LEVEL);
    this_player()->set_skill("leg",SKILLS_LEVEL);
    this_player()->set_skill("tenglong-bifa",SKILLS_LEVEL);
    this_player()->set_skill("dagger",SKILLS_LEVEL);
    this_player()->set_skill("dulong-dafa",SKILLS_LEVEL);
    this_player()->set_skill("youlong-shenfa",SKILLS_LEVEL);
    this_player()->set_skill("poison",180);
    this_player()->set_skill("shenlong-wudizhen",SKILLS_LEVEL);
    this_player()->set_skill("shenlong-yaoli",SKILLS_LEVEL);
    this_player()->set("shen",-100000);
    this_player()->set("shizhe_拜师",1);
	this_player()->set("family/master_id","hong antong");
	this_player()->set("family/master_name","洪安通");
    return "hehe";
}
string ask_tls()
{
    object ob;
    ob=this_player();
    if (this_player()->query("shizhe_拜师")) return "你不是要过一次门派skills了嘛！？\n";
   if (!this_player()->query("shizhe_newbie")) return "你必须要先ask shizhe about newbie！？\n";
    if((string)ob->query("gender") == "女性" )
    return "天龙寺武功需要纯阳之体，小姑娘可不收啊! ";
    message_vision(HIY "使者"+ NOR "一挥手，一阵狂风将$N吹得无影无踪了。"+ NOR "\n",this_player());
    this_object()->create_family("天龙寺", 99, "弟子");
    this_object()->recruit_apprentice(this_player());
    this_player()->move("/d/dali/shanhou");
    this_player()->set_skill("qingyan-zhang",SKILLS_LEVEL);
	this_player()->set_skill("whip",SKILLS_LEVEL);
	this_player()->set_skill("cihang-bian",SKILLS_LEVEL);
    this_player()->set_skill("kurong-changong",SKILLS_LEVEL);
    this_player()->set_skill("qiantian-yiyang",SKILLS_LEVEL);
    this_player()->set_skill("kurong-changong",SKILLS_LEVEL);
	this_player()->set_skill("liumai-shenjian",SKILLS_LEVEL);
    this_player()->set_skill("strike",SKILLS_LEVEL);
    this_player()->set_skill("sword",SKILLS_LEVEL);
	this_player()->set_skill("axe",SKILLS_LEVEL);
    this_player()->set_skill("pangen-fu",SKILLS_LEVEL);
    this_player()->set_skill("brush",SKILLS_LEVEL);
    this_player()->set_skill("yingou-bifa",SKILLS_LEVEL);

    this_player()->set_skill("whip",SKILLS_LEVEL);
    this_player()->set_skill("tianlong-xiang",SKILLS_LEVEL);
    this_player()->set_skill("finger",SKILLS_LEVEL);
    this_player()->set_skill("buddhism",200);
    this_player()->set_skill("kurong-changong",SKILLS_LEVEL);
    this_player()->set_skill("duanjia-jianfa",SKILLS_LEVEL);
    this_player()->set_skill("yiyang-zhi",SKILLS_LEVEL);
    this_player()->set("shen",100000);
	this_player()->set("yideng/ronghe","pass");
	this_player()->set("quest/tls/zhijian/pass",1);
	this_player()->set("quest/tls/liumai/pass",1);
	this_player()->set("quest/tls/yiyangshu/pass",1);
	this_player()->set("quest/tls/ailao/pass",1);
	this_player()->add("liumai-shenjian/zhongchong",1);
	this_player()->add("liumai-shenjian/shangyang",1);
	this_player()->add("liumai-shenjian/shaoshang",1);
	this_player()->add("liumai-shenjian/shaochong",1);
	this_player()->add("liumai-shenjian/guanchong",1);
	this_player()->add("liumai-shenjian/shaoze",1);
    this_player()->set("shizhe_拜师",1);
    return "hehe";
}
string ask_xs()
{
    if (this_player()->query("shizhe_拜师")) return "你不是要过一次门派skills了嘛！？\n";
   if (!this_player()->query("shizhe_newbie")) return "你必须要先ask shizhe about newbie！？\n";
    message_vision(HIY "使者"+ NOR "一挥手，一阵狂风将$N吹得无影无踪了。"+ NOR "\n",this_player());
    this_object()->create_family("大轮寺", 99, "弟子");
    this_object()->recruit_apprentice(this_player());
    //this_player()->move("/d/xueshan/guangchang");
    this_player()->set_skill("dodge",SKILLS_LEVEL);
    this_player()->set_skill("force",SKILLS_LEVEL);
    this_player()->set_skill("huanxi-chan",200);
    this_player()->set_skill("huoyan-dao",SKILLS_LEVEL);
    this_player()->set_skill("longxiang-boruo",SKILLS_LEVEL);
    this_player()->set_skill("parry",SKILLS_LEVEL);
    this_player()->set_skill("strike",SKILLS_LEVEL);
    this_player()->set_skill("hand",SKILLS_LEVEL);
	this_player()->set_skill("dashou-yin",SKILLS_LEVEL);
    this_player()->set_skill("blade",SKILLS_LEVEL);
    this_player()->set_skill("hammer",SKILLS_LEVEL);
    this_player()->set_skill("yuxue-dunxing",SKILLS_LEVEL);
    this_player()->set_skill("xuedao-jing",SKILLS_LEVEL);
    this_player()->set_skill("xiangfu-lun",SKILLS_LEVEL);
	this_player()->set_skill("staff",SKILLS_LEVEL);
	this_player()->set_skill("wushang-dali",SKILLS_LEVEL);
	this_player()->set_skill("claw",SKILLS_LEVEL);
	this_player()->set_skill("tianwang-zhua",SKILLS_LEVEL);
	this_player()->set_skill("poison",100);
    this_player()->set("shen",100000);
    this_player()->set("shen",-100000);
    this_player()->set("shizhe_拜师",1);
	this_player()->set("quest/dls/longxiang/pass",1);
	this_player()->set("quest/dls/hyd/pass",1);
    this_player()->set("quest/wulun/pass",1);
	this_player()->set("lx",11);
    return "hehe";
}
string ask_kl()
{
    if (this_player()->query("shizhe_拜师")) return "你不是要过一次门派skills了嘛！？\n";
   if (!this_player()->query("shizhe_newbie")) return "你必须要先ask shizhe about newbie！？\n";
    message_vision(HIY "使者"+ NOR "一挥手，一阵狂风将$N吹得无影无踪了。"+ NOR "\n",this_player());
    this_object()->create_family("昆仑派", 99, "弟子");
    this_object()->recruit_apprentice(this_player());
   // this_player()->move("/d/kunlun/guangchang");
    this_player()->set_skill("xuantian-wuji",SKILLS_LEVEL);
    this_player()->set_skill("taxue-wuhen",SKILLS_LEVEL);
    this_player()->set_skill("chuanyun-tui",SKILLS_LEVEL);
    this_player()->set_skill("kunlun-zhang",SKILLS_LEVEL);
    this_player()->set_skill("zhentian-quan",SKILLS_LEVEL);
    this_player()->set_skill("liangyi-jian",SKILLS_LEVEL);
    this_player()->set_skill("xunlei-jian",SKILLS_LEVEL);
    //this_player()->set_skill("mantian-huayu",SKILLS_LEVEL);
    this_player()->set_skill("strike",SKILLS_LEVEL);
    this_player()->set_skill("cuff",SKILLS_LEVEL);
    this_player()->set_skill("sword",SKILLS_LEVEL);
    this_player()->set_skill("force",SKILLS_LEVEL);
    this_player()->set_skill("leg",SKILLS_LEVEL);
    this_player()->set_skill("parry",SKILLS_LEVEL);
    this_player()->set_skill("dodge",SKILLS_LEVEL);
   // this_player()->set_skill("throwing",SKILLS_LEVEL);
    this_player()->set_skill("art",200);
    this_player()->set("shen",100000);
    this_player()->set("shizhe_拜师",1);

    return "hehe";
}

string ask_baixing()
{
    if (this_player()->query("shizhe_拜师")) return "你不是要过一次门派skills了嘛！？\n";
    if (!this_player()->query("shizhe_newbie")) return "你必须要先ask shizhe about newbie！？\n";
    message_vision(HIY "使者"+ NOR "一挥手，一阵狂风将$N吹得无影无踪了。"+ NOR "\n",this_player());
    this_object()->create_family("百姓", 1, "弟子");
    this_object()->recruit_apprentice(this_player());
    this_object()->delete("title");
   // this_player()->move("/d/songshan/damen");
    this_player()->set_skill("taixuan-gong",SKILLS_LEVEL);
	this_player()->set_skill("luohan-fumogong",SKILLS_LEVEL);
	this_player()->set_skill("beiming-shengong",SKILLS_LEVEL);
	this_player()->set_skill("lingbo-weibu",SKILLS_LEVEL);
	this_player()->set_skill("shenzhao-jing",SKILLS_LEVEL);
    this_player()->set_skill("blade",SKILLS_LEVEL);
    this_player()->set_skill("hujia-daofa",SKILLS_LEVEL);
	this_player()->set_skill("miaojia-jianfa",SKILLS_LEVEL);
    this_player()->set_skill("cuff",SKILLS_LEVEL);
    this_player()->set_skill("taizu-quan",SKILLS_LEVEL);
    this_player()->set_skill("shexing-lifan",SKILLS_LEVEL);
    this_player()->set_skill("tangshi-jianfa",SKILLS_LEVEL);
    this_player()->set_skill("wuhu-duanmendao",SKILLS_LEVEL);
    this_player()->set_skill("claw",SKILLS_LEVEL);
    this_player()->set_skill("jiuyin-baiguzhua",SKILLS_LEVEL);
    this_player()->set_skill("strike",SKILLS_LEVEL);
    this_player()->set_skill("cuixin-zhang",SKILLS_LEVEL);
    this_player()->set_skill("dodge",SKILLS_LEVEL);
    this_player()->set_skill("parry",SKILLS_LEVEL);
    this_player()->set("shen",0);
    //this_player()->set("job_time/嵩山",500);
    //this_player()->set("songshan_points",600);
    this_player()->set("shizhe_拜师",1);
    return "hehe";
}

string ask_quanzhen()
{
    if (this_player()->query("shizhe_拜师")) return "你不是要过一次门派skills了嘛！？\n";
   if (!this_player()->query("shizhe_newbie")) return "你必须要先ask shizhe about newbie！？\n";
    message_vision(HIY "使者"+ NOR "一挥手，一阵狂风将$N吹得无影无踪了。"+ NOR "\n",this_player());
    this_object()->create_family("全真教", 99, "弟子");
    this_object()->recruit_apprentice(this_player());
    // this_player()->move("/d/kunlun/guangchang");
    this_player()->set_skill("xiantian-gong",SKILLS_LEVEL);
    this_player()->set_skill("jinyan-gong",SKILLS_LEVEL);
    this_player()->set_skill("quanzhen-jianfa",SKILLS_LEVEL);
    this_player()->set_skill("haotian-zhang",SKILLS_LEVEL);
    this_player()->set_skill("kongming-quan",SKILLS_LEVEL);
  //  this_player()->set_skill("tiangang-beidouzhen",SKILLS_LEVEL);
    //this_player()->set_skill("xunlei-jian",SKILLS_LEVEL);
    //this_player()->set_skill("mantian-huayu",SKILLS_LEVEL);
    this_player()->set_skill("strike",SKILLS_LEVEL);
    this_player()->set_skill("cuff",SKILLS_LEVEL);
    this_player()->set_skill("sword",SKILLS_LEVEL);
    this_player()->set_skill("force",SKILLS_LEVEL);
    //this_player()->set_skill("leg",SKILLS_LEVEL);
    this_player()->set_skill("parry",SKILLS_LEVEL);
    this_player()->set_skill("dodge",SKILLS_LEVEL);
   // this_player()->set_skill("throwing",SKILLS_LEVEL);
    this_player()->set_skill("taoism",200);
    this_player()->set("shen",100000);
	this_player()->set("quanzhen/force",1);
	this_player()->set("qixing/pass",1);
    this_player()->set("shizhe_拜师",1);

    return "hehe";
}

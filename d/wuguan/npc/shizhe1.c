
#include <ansi.h>
#define Weapon_LEVEL            100
#define SKILLS_LEVEL            251

#define KNOWLEDGE_LEVEL         300

#define GIVE_EXP                1750000

#define MAX_NEILI               8000

#define MAX_JINGLI              4000

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

string ask_mur();
string ask_tttt();
string ask_xuedao();
string ask_thd();
string ask_tz();
string ask_tls();
string ask_ljg();
object ob = this_object();
void create()
{
    set_name(HIC"�齣����ʹ��(ǰ��)"NOR, ({ "shizheb" }));
    set("long", HIW"�����ask shizhe about newbie,��ask shizhe about ��ʦ,ϲ���ĸ����ɾ�ask shizhe about ***(����),addoil all \n"NOR);
    set("gender", "����");
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
		 "����" : (: ask_fanhui :),
        "��ʦ" : "��Ҫ�������ask shizhe about ���������ơ���\n�䵱�����֣����ޣ�������̣����չ�����ɽ��ؤ������������أ����ƣ�\n��Ĺ��Ľ�ݣ��һ����������£������£���ɽ�����̣�����?\n����� ask ��û�з�Ӧ�ģ���ô�����Ǹ������Ѿ��ر��ˡ�\n",
        "������" : (: ask_xs :),
        "�һ���" : (: ask_thd :),
        "����" : (: ask_xingxiu :),
        "�䵱" : (: ask_wudang :),
        "����" : (: ask_emei :),
        "����" : (: ask_mingjiao :),
        "����" : (: ask_shaolin :),
	    "Ѫ����" : (: ask_xuedao :),
		"�������" : (: ask_riyue :),
        "ؤ��" : (: ask_gb :),
        "��Ĺ" : (: ask_tttt :),
        "��ɽ" : (: ask_hs :),
        "��ɽ" : (: ask_ss :),
        "Ľ��" : (: ask_mur :),
        "������" : (: ask_tls :),
        "����" : (: ask_tz :),
        "������" : (: ask_sld :),
			"���չ�" : (: ask_ljg :),
        "����" : (: ask_kl :),
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
    write ("������ ask shizhe about ��ʦ ��Ҫ���ܡ�\n");
    ob->set_skill("dodge",1);
    skill = ob->query_skills();
    skl = keys(skill);
    i = sizeof(skl);
    while (i--) 
    {
      ob->delete_skill(skl[i]);              
    }
    message_vision(HIC"�齣����ʹ�߷�ȥ����������书��\n"NOR,me,ob);
    message_vision(HIW"����������һ��Ĺ������ʱ�䣡\n"NOR,me,ob);
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
    ob->set("job_time/ؤ��",400);
    ob->set("shizhe_newbie",1);
    ob->set("registered", 3);    
    ob->set("vip/vip_time",time());
    ob->add("vip/vip_time",365*24*3600);
	ob->set("vip/vip_start_time",time());    
    ob->set("age",25);
    ob->set("mud_age",1000000);
    ob->set("enter_wuguan",0);
    if(objectp(letter = new(__DIR__"obj/letter")))
        {        
        command("say �����ﻹ��һ������Ƽ��ţ��������ȥ�ɣ����չ�����˰ɣ�");
        letter->move(ob);
        message_vision(""HIW"�齣����ʹ��"NOR"����һ�⡸"+letter->query("name")+"����\n",me,  this_object());   
        return "����㲻��ұ������֮��������ʹ�� help dazao �����ϸ��Ϣ��"; 
        }
    return "Ϊ����newbie�ش˽���!���� ask shizhe about ��ʦ ��Ҫ���ܡ�\n"; 
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
    message_vision(HIC"�齣����ʹ�߷�ȥ����������书��\n"NOR,me,ob);
    ob->delete("shizhe_newbie");
    ob->delete("shizhe_��ʦ");
    ob->delete("mishu_newbie");
    ob->delete("mishu_want");
    ob->set("family",0);
    return "������ask shizhe about newbieһ�Ρ�\n";
}
string ask_riyue()
{
    if (this_player()->query("shizhe_��ʦ")) return "�㲻��Ҫ��һ������skills�����\n";
    if (!this_player()->query("shizhe_newbie")) return "�����Ҫ��ask shizhe about newbie����\n";
    message_vision(HIY "ʹ��"+ NOR "һ���֣�һ���罫$N������Ӱ�����ˡ�"+ NOR "\n",this_player());
    this_object()->create_family("�������", 10, "����");
    this_object()->recruit_apprentice(this_player());
    this_object()->delete("title");
    //this_player()->move("/d/xingxiu/xxh");
    this_player()->set("job_time/����",5000);
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
	this_player()->set_skill("strike",SKILLS_LEVEL);
	this_player()->set_skill("dali-shenmofu",SKILLS_LEVEL);
    this_player()->set_skill("axe",SKILLS_LEVEL);
    this_player()->set_skill("sword",SKILLS_LEVEL);
    this_player()->set_skill("qixian-wuxingjian",SKILLS_LEVEL);
	this_player()->set_skill("throwing",SKILLS_LEVEL);
    this_player()->set_skill("mantian-huayu",SKILLS_LEVEL);
    this_player()->set_skill("poison",150);
    this_player()->set("shizhe_��ʦ",1);
    this_player()->set_skill("poison",150);
    this_player()->set("shizhe_��ʦ",1);
    this_player()->set("shen",-100000);
	this_player()->set("hmy/quest/tmgf",1);
    return "hehe";
}
string ask_xingxiu()
{
    if (this_player()->query("shizhe_��ʦ")) return "�㲻��Ҫ��һ������skills�����\n";
    if (!this_player()->query("shizhe_newbie")) return "�����Ҫ��ask shizhe about newbie����\n";
    message_vision(HIY "ʹ��"+ NOR "һ���֣�һ���罫$N������Ӱ�����ˡ�"+ NOR "\n",this_player());
    this_object()->create_family("������", 2, "����");
    this_object()->recruit_apprentice(this_player());
    this_object()->delete("title");
    this_player()->move("/d/xingxiu/xxh");
    this_player()->set("job_time/����",5000);
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
    this_player()->set("shizhe_��ʦ",1);
    this_player()->set("shen",-100000);
    return "hehe";
}
string ask_ljg()
{
    if (this_player()->query("shizhe_��ʦ")) return "�㲻��Ҫ��һ������skills�����\n";
    if (!this_player()->query("shizhe_newbie")) return "�����Ҫ��ask shizhe about newbie����\n";
    message_vision(HIY "ʹ��"+ NOR "һ���֣�һ���罫$N������Ӱ�����ˡ�"+ NOR "\n",this_player());
    this_object()->create_family("���չ�", 3, "����");
    this_object()->recruit_apprentice(this_player());
    this_object()->delete("title");
    //this_player()->move("/d/xingxiu/xxh");
   // this_player()->set("job_time/����",5000);
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
    this_player()->set("shizhe_��ʦ",1);
    this_player()->set("shen",0);
    this_player()->set("quest/tonglao/pass",1);
    return "hehe";
}
string ask_xuedao()
{
    if (this_player()->query("shizhe_��ʦ")) return "�㲻��Ҫ��һ������skills�����\n";
    if (!this_player()->query("shizhe_newbie")) return "�����Ҫ��ask shizhe about newbie����\n";
    message_vision(HIY "ʹ��"+ NOR "һ���֣�һ���罫$N������Ӱ�����ˡ�"+ NOR "\n",this_player());
    this_object()->create_family("Ѫ����", 3, "����");
    this_object()->recruit_apprentice(this_player());
    this_object()->delete("title");
    this_player()->move("/d/xingxiu/xxh");
     this_player()->set("job_time/ѩɽ",5000);
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
    this_player()->set("shizhe_��ʦ",1);
    this_player()->set("shen",-100000);
    return "hehe";
}
string ask_ss()
{
    if (this_player()->query("shizhe_��ʦ")) return "�㲻��Ҫ��һ������skills�����\n";
    if (!this_player()->query("shizhe_newbie")) return "�����Ҫ��ask shizhe about newbie����\n";
    message_vision(HIY "ʹ��"+ NOR "һ���֣�һ���罫$N������Ӱ�����ˡ�"+ NOR "\n",this_player());
    this_object()->create_family("��ɽ��", 4, "����");
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
    this_player()->set("job_time/��ɽ",5000);
    this_player()->set("songshan_points",6000);
    this_player()->set("shizhe_��ʦ",1);
    return "hehe";
}
string ask_wudang()
{
    if (this_player()->query("shizhe_��ʦ")) return "�㲻��Ҫ��һ������skills�����\n";
    if (!this_player()->query("shizhe_newbie")) return "�����Ҫ��ask shizhe about newbie����\n";
    message_vision(HIY "ʹ��"+ NOR "һ���֣�һ���罫$N������Ӱ�����ˡ�"+ NOR "\n",this_player());
    this_object()->create_family("�䵱��", 5, "����");
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
    this_player()->set_skill("cuff",SKILLS_LEVEL);
    this_player()->set_skill("blade",SKILLS_LEVEL);
	this_player()->set_skill("xuanxu-daofa",SKILLS_LEVEL);
    this_player()->set("shen",100000);
    this_player()->set("shizhe_��ʦ",1);
    return "hehe";
}
string ask_emei()
{
    object ob;
    ob=this_player();
    if (ob->query("shizhe_��ʦ")) return "�㲻��Ҫ��һ������skills�����\n";
   if (!this_player()->query("shizhe_newbie")) return "�����Ҫ��ask shizhe about newbie����\n";
    message_vision(HIY "ʹ��"+ NOR "һ���֣�һ���罫$N������Ӱ�����ˡ�"+ NOR "\n",this_player());
    this_object()->create_family("������", 5, "����");
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

    this_player()->set_skill("sixiang-zhang",SKILLS_LEVEL);
    this_player()->set_skill("parry",SKILLS_LEVEL);
    this_player()->set_skill("linji-zhuang",SKILLS_LEVEL);
    this_player()->set_skill("strike",SKILLS_LEVEL);
    this_player()->set_skill("sword",SKILLS_LEVEL);
    this_player()->set("shizhe_��ʦ",1);
    return "hehe";
}
string ask_shaolin()
{
object ob;
ob=this_player();
if (ob->query("shizhe_��ʦ")) return "�㲻��Ҫ��һ������skills�����\n";
   if (!ob->query("shizhe_newbie")) return "�����Ҫ��ask shizhe about newbie����\n";
if((string)ob->query("gender") == "Ů��" )
return "�������书��Ҫ����֮�壬С����ɲ��հ�! ";
message_vision(HIY "ʹ��"+ NOR "һ���֣�һ���罫$N������Ӱ�����ˡ�"+ NOR "\n",this_player());
this_object()->create_family("������", 99, "����");
this_object()->recruit_apprentice(this_player());
this_object()->delete("title");       
this_player()->move("/d/shaolin/smdian");
this_player()->set_skill("buddhism",200);
this_player()->set_skill("jingang-quan",SKILLS_LEVEL);//6�߼�
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
        //3 weapon ���ǲ���������ѧֻ�������Լ�ѡ��
this_player()->set_skill("blade",SKILLS_LEVEL);
this_player()->set_skill("club",SKILLS_LEVEL);
this_player()->set_skill("whip",SKILLS_LEVEL);
this_player()->set_skill("yijin-jing",SKILLS_LEVEL);
this_player()->set_skill("shaolin-shenfa",SKILLS_LEVEL);

    this_player()->set("shen",100000);
    this_player()->set("shizhe_��ʦ",1);
    return "hehe";
}
string ask_mingjiao()
{
    if (this_player()->query("shizhe_��ʦ")) return "�㲻��Ҫ��һ������skills�����\n";
   if (!this_player()->query("shizhe_newbie")) return "�����Ҫ��ask shizhe about newbie����\n";
    message_vision(HIY "ʹ��"+ NOR "һ���֣�һ���罫$N������Ӱ�����ˡ�"+ NOR "\n",this_player());
    this_object()->create_family("����", 37, "����");
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
	//this_player()->set("mj/jiuyang/pass",3);
	this_player()->set("mjyzs/pass",1);
    this_player()->set("shizhe_��ʦ",1);
    return "hehe";
}

string ask_gb()
{
    if (this_player()->query("shizhe_��ʦ")) return "�㲻��Ҫ��һ������skills�����\n";
   if (!this_player()->query("shizhe_newbie")) return "�����Ҫ��ask shizhe about newbie����\n";
    message_vision(HIY "ʹ��"+ NOR "һ���֣�һ���罫$N������Ӱ�����ˡ�"+ NOR "\n",this_player());
    this_object()->create_family("ؤ��", 99, "����");
    this_object()->recruit_apprentice(this_player());
    this_object()->delete("title");        
    this_player()->move("/d/gb/pomiao");
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
    this_player()->set("job_time/ץ��",1000);
    this_player()->set("job_time/ؤ��",1000);
    this_player()->set("job_time/��ɱ",1000);
    this_player()->set("job_time/��Ħ��",1000);
    this_player()->set("gb/gift", 1);
    //this_player()->set("xlz/hang", 1)
// ɾ������quest �Ǻ�
    this_player()->set("dgb/wugou",1);
    this_player()->set("xlz/hang",1);
	this_player()->set("kanglong/pass",1);
    this_player()->set("xlz/sanzhao","pass");
    this_player()->set("shizhe_��ʦ",1);
    return "hehe";
}
string ask_hs()
{
    if (this_player()->query("shizhe_��ʦ")) return "�㲻��Ҫ��һ������skills�����\n";
    if (!this_player()->query("shizhe_newbie")) return "�����Ҫ��ask shizhe about newbie����\n";
    message_vision(HIY "ʹ��"+ NOR "һ���֣�һ���罫$N������Ӱ�����ˡ�"+ NOR "\n",this_player());
    this_object()->create_family("��ɽ��", 99, "����");
    this_object()->recruit_apprentice(this_player());
    this_object()->delete("title");
    this_player()->move("/d/huashan/zhengqi");
    this_player()->set_skill("huashan-shenfa",SKILLS_LEVEL);
    this_player()->set_skill("claw",SKILLS_LEVEL);
	//this_player()->set_skill("dugu-jiujian",SKILLS_LEVEL);
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
    this_player()->set("shen",100000);
    this_player()->set("job_time/ؤ��",1000);
    this_player()->set("shizhe_��ʦ",1);
	this_player()->set("quest/zixia/pass",1);
    return "hehe";
}
string ask_tttt()
{
//object suo
    if (this_player()->query("shizhe_��ʦ")) return "�㲻��Ҫ��һ������skills�����\n";
   if (!this_player()->query("shizhe_newbie")) return "�����Ҫ��ask shizhe about newbie����\n";
    if (this_player()->query("per") < 25)
     return "��������òǷ��, ���½�����Բ˫���ϱ�֮���Ρ�\n";
    message_vision(HIY "ʹ��"+ NOR "һ���֣�һ���罫$N������Ӱ�����ˡ�"+ NOR "\n",this_player());
    this_object()->create_family("��Ĺ��", 99, "����");
    this_object()->recruit_apprentice(this_player());
    this_object()->delete("title");
   //  this_player()->move("/d/gumu/jqg/wshi");
//����GM ����˧������
    this_player()->set_skill("strike",SKILLS_LEVEL);    
    this_player()->set_skill("sword",SKILLS_LEVEL);
    this_player()->set_skill("hand",SKILLS_LEVEL);
    this_player()->set_skill("whip",SKILLS_LEVEL);    
    this_player()->set_skill("cuff",SKILLS_LEVEL);            
    this_player()->set_skill("yunu-xinjing",SKILLS_LEVEL);
    this_player()->set_skill("yunu-shenfa",SKILLS_LEVEL);
    this_player()->set_skill("yunu-jianfa",SKILLS_LEVEL);
    this_player()->set_skill("xuantie-jianfa",SKILLS_LEVEL);
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
  /*  if (this_player()->query("gender")!="Ů��") {
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
	this_player()->set("quest/jiuyingm/pass",1);
    this_player()->set("shizhe_��ʦ",1);
    return "hehe";
}
string ask_mur()
{
    if (this_player()->query("shizhe_��ʦ")) return "�㲻��Ҫ��һ������skills�����\n";
   if (!this_player()->query("shizhe_newbie")) return "�����Ҫ��ask shizhe about newbie����\n";
    message_vision(HIY "ʹ��"+ NOR "һ���֣�һ���罫$N������Ӱ�����ˡ�"+ NOR "\n",this_player());
    this_object()->create_family("����Ľ��", 99, "����");
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
    this_player()->set("shizhe_��ʦ",1);
    return "hehe";
}
string ask_thd()
{
    if (this_player()->query("shizhe_��ʦ")) return "�㲻��Ҫ��һ������skills�����\n";
   if (!this_player()->query("shizhe_newbie")) return "�����Ҫ��ask shizhe about newbie����\n";
    message_vision(HIY "ʹ��"+ NOR "һ���֣�һ���罫$N������Ӱ�����ˡ�"+ NOR "\n",this_player());
    this_object()->create_family("�һ���", 99, "����");
    this_object()->recruit_apprentice(this_player());
    this_object()->delete("title");   
    //this_player()->move("/d/thd/jicui");
    this_player()->set("job_time/�һ���",400);
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
    this_player()->set("shizhe_��ʦ",1);
	this_player()->set("thd/wuji/luoying",1);
	this_player()->set("thd/wuji/yuxiao",1);
    this_player()->set("thd/wuji/kuangfeng",1);
	this_player()->set("thd/wuji/lingxi",1);
	 this_player()->set("thd/wuji/huayu",1);
	this_player()->set("thd/wuji/lhs",1);
    this_player()->set("thd/finish",1);
	this_player()->set("thdjj/ronghe","pass"); 
	message_vision(HIC"��ע�⣬�һ���ֻ�н⿪ÿһ���似��Сquestion���������ܳ����ͷš�(��Ϭһָ����硣����)\n",this_player());
    return "hehe";
}
string ask_tz()
{
 if (!this_player()->query("shizhe_newbie")) return "�����Ҫ��ask shizhe about newbie����\n";
  if (this_player()->query("shizhe_��ʦ")) return "�㲻��Ҫ��һ������skills�����\n";
    message_vision(HIY "ʹ��"+ NOR "һ���֣�һ���罫$N������Ӱ�����ˡ�"+ NOR "\n",this_player());
    this_object()->create_family("���ư�", 99, "����");
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
    this_player()->set("job_time/����",400);
    this_player()->set("shen",-100000);
    this_player()->set("shizhe_��ʦ",1);
    this_player()->set("quest/tzauto/over",1);
	this_player()->set("tiezhang/pass",1);
	this_player()->set("quest/tiezhang/piao",1);
	message_vision(HIC"��ע�⣬�ں��Ѿ�����\n",this_player());
    return "hehe";
}
string ask_sld()
{
    if (this_player()->query("shizhe_��ʦ")) return "�㲻��Ҫ��һ������skills�����\n";
   if (!this_player()->query("shizhe_newbie")) return "�����Ҫ��ask shizhe about newbie����\n";
    message_vision(HIY "ʹ��"+ NOR "һ���֣�һ���罫$N������Ӱ�����ˡ�"+ NOR "\n",this_player());
    this_object()->create_family("������", 99, "����");
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
    this_player()->set_skill("shenlong-tuifa",SKILLS_LEVEL);
    this_player()->set_skill("leg",SKILLS_LEVEL);
    this_player()->set_skill("tenglong-bifa",SKILLS_LEVEL);
    this_player()->set_skill("dagger",SKILLS_LEVEL);
    this_player()->set_skill("dulong-dafa",SKILLS_LEVEL);
    this_player()->set_skill("youlong-shenfa",SKILLS_LEVEL);
    this_player()->set_skill("poison",180);
	 this_player()->set_skill("chansi-shou",SKILLS_LEVEL);
    this_player()->set_skill("hand",SKILLS_LEVEL);
    this_player()->set_skill("shenlong-wudizhen",SKILLS_LEVEL);
    this_player()->set_skill("shenlong-yaoli",SKILLS_LEVEL);
    this_player()->set("shen",-100000);
    this_player()->set("shizhe_��ʦ",1);
	this_player()->set("family/master_id","hong antong");
	this_player()->set("family/master_name","�鰲ͨ");
    return "hehe";
}
string ask_tls()
{
    object ob;
    ob=this_player();
    if (this_player()->query("shizhe_��ʦ")) return "�㲻��Ҫ��һ������skills�����\n";
   if (!this_player()->query("shizhe_newbie")) return "�����Ҫ��ask shizhe about newbie����\n";
    if((string)ob->query("gender") == "Ů��" )
    return "�������书��Ҫ����֮�壬С����ɲ��հ�! ";
    message_vision(HIY "ʹ��"+ NOR "һ���֣�һ���罫$N������Ӱ�����ˡ�"+ NOR "\n",this_player());
    this_object()->create_family("������", 99, "����");
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
    this_player()->set_skill("whip",SKILLS_LEVEL);
    this_player()->set_skill("tianlong-xiang",SKILLS_LEVEL);
    this_player()->set_skill("finger",SKILLS_LEVEL);
    this_player()->set_skill("buddhism",200);
		this_player()->set_skill("axe",SKILLS_LEVEL);
    this_player()->set_skill("pangen-fu",SKILLS_LEVEL);
    this_player()->set_skill("brush",SKILLS_LEVEL);
    this_player()->set_skill("yingou-bifa",SKILLS_LEVEL);

    this_player()->set_skill("kurong-changong",SKILLS_LEVEL);
    this_player()->set_skill("duanjia-jianfa",SKILLS_LEVEL);
    this_player()->set_skill("yiyang-zhi",SKILLS_LEVEL);
    this_player()->set("shen",100000);
	this_player()->set("yideng/ronghe","pass");
    this_player()->set("shizhe_��ʦ",1);
    return "hehe";
}
string ask_xs()
{
    if (this_player()->query("shizhe_��ʦ")) return "�㲻��Ҫ��һ������skills�����\n";
   if (!this_player()->query("shizhe_newbie")) return "�����Ҫ��ask shizhe about newbie����\n";
    message_vision(HIY "ʹ��"+ NOR "һ���֣�һ���罫$N������Ӱ�����ˡ�"+ NOR "\n",this_player());
    this_object()->create_family("������", 99, "����");
    this_object()->recruit_apprentice(this_player());
    this_player()->move("/d/xueshan/guangchang");
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
    
    this_player()->set("shizhe_��ʦ",1);
    return "hehe";
}
string ask_kl()
{
    if (this_player()->query("shizhe_��ʦ")) return "�㲻��Ҫ��һ������skills�����\n";
   if (!this_player()->query("shizhe_newbie")) return "�����Ҫ��ask shizhe about newbie����\n";
    message_vision(HIY "ʹ��"+ NOR "һ���֣�һ���罫$N������Ӱ�����ˡ�"+ NOR "\n",this_player());
    this_object()->create_family("������", 99, "����");
    this_object()->recruit_apprentice(this_player());
    this_player()->move("/d/kunlun/guangchang");
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
    this_player()->set("shizhe_��ʦ",1);

    return "hehe";
}

string ask_baixing()
{
    if (this_player()->query("shizhe_��ʦ")) return "�㲻��Ҫ��һ������skills�����\n";
    if (!this_player()->query("shizhe_newbie")) return "�����Ҫ��ask shizhe about newbie����\n";
    message_vision(HIY "ʹ��"+ NOR "һ���֣�һ���罫$N������Ӱ�����ˡ�"+ NOR "\n",this_player());
    this_object()->create_family("����", 1, "����");
    this_object()->recruit_apprentice(this_player());
    this_object()->delete("title");
   // this_player()->move("/d/songshan/damen");
    this_player()->set_skill("taixuan-gong",SKILLS_LEVEL);
	this_player()->set_skill("luohan-fumogong",SKILLS_LEVEL);
	//this_player()->set_skill("beiming-shengong",SKILLS_LEVEL);
	//this_player()->set_skill("lingbo-weibu",SKILLS_LEVEL);
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
    //this_player()->set("job_time/��ɽ",500);
    //this_player()->set("songshan_points",600);
    this_player()->set("shizhe_��ʦ",1);
    return "hehe";
}
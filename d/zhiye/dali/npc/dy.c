// duanyu.c ����
// COOL@SJ,990827
// Modified by tangfeng 2004
// ����Ķ����漰������������һ������������һ����ʯ���һ���ڴ����°�����
// By Spiderii@ty ����ʱ������
inherit F_MASTER;
#include <ansi.h>
inherit NPC;

#define QUESTDIR "quest/�����˲�/"
#define QUESTDIR1 "quest/�����˲�/�貨΢��ƪ/"
#define QUESTDIR2 "quest/�����˲�/����Ӫ��ƪ/"
#define QUESTDIR3 "quest/�����˲�/��������ƪ/"
#define QUESTDIR4 "quest/�����˲�/���ɾ�Ԯƪ/"
#define QUESTDIR5 "quest/�����˲�/��������ƪ/"
#define QUESTDIR6 "quest/�����˲�/�书/"

string tianlonghelp();
string askxiaofeng();
string askjiumozhi();
string ask_name();
int ask_home();
int ask_save();
void outroom(object me);
void dest(object me,object ob);
void greeting(object me);

void create()
{
        set_name("����", ({"duan yu", "duan", "duayu"}));
        set("gender", "����");
        set("age", 20);
		set("title",HIG"���������������"NOR);

        set("long", "����һ���������ӣ���һ����ɫ���ۣ��������񣬳ݰ״��죬���ʸ��š�\n"
                    "����Ϊ�峺��һ�����Ǿþ�Ѭ�ն����ɵ������������ӣ����������ң�ȴ���ɷ�����ˡ�\n");
        set("attitude", "peaceful");
        set("str", 40);
        set("per", 40);
        set("int", 40);
        set("con", 40);
        set("dex", 40);
        //set("no_quest", 1);

        set("inquiry", ([
		"����" : (: ask_name :),
		"name" : (: ask_name :),
		"���" : (: ask_save :),
		"����" : (: ask_save :),
		"�ȶ���" : (: ask_save :),
		"������" : (: ask_save :),
		"���" : (: ask_save :),
		"���" : (: ask_save :),
		"save" : (: ask_save :),
		"������" : "���������ҹؽ����ġ�\n",
		"��ʦ" : "��....���ҵ�ʦ�������ӡ����Ӻ�ׯ�ӣ����ǵ�ѧ���һ�ûѧȫ�ء�\n",
		"����" : "�������Ҽң��Ҽ��ڴ���",
		"������" : "�������Ǵ���μ���ѧ�����֮�ء�",
		"��������" : (: tianlonghelp :),
		"����" : "�Ҵ�����尡���˵�һ���ú���",
		"Ӫ������" : (: askxiaofeng :),
		"Ľ�ݸ�" : "Ľ�ݹ���ȷ���佭���Ĳɣ�ʫ���黭�����������书���ǹھ����¡�",
		"Ľ�ݲ�" : "����˵�ǣ�����Ľ�ݲ����Ľܲţ���ϧӢ�����š�",
		"�Ħ��" : (: askjiumozhi :),
		"������" : "��������߾�ѧ��",
		"������" : "�����ҵ�����",
		"���׷�" : "������������ʲô���飿",
		"������" : "�����Ҳ�����ʲô���飿",
		"����" : "������������ʲô���飿",

		"�ؼ�" : (: ask_home :),
		"go home" : (: ask_home :),

		//�����񽣵�quest������������һ�룬�ڿ��ٳ��������в�������
        ]));

        set("jing", 10000);
        set("max_jing", 10000);
        set("jingli", 10000);
        set("eff_jingli", 10000);
        set("qi", 80000);
        set("max_qi", 80000);
        set("neili", 80000);
        set("max_neili", 80000);
        set("jiali",250);
		//Ҫ�趨��ڤ���貨����
        
        set("combat_exp", 15000000);
        set_skill("buddhism", 250);            
        //set_skill("daode-jing", 250);                   
        set_skill("literate", 400);                
        set_skill("force", 550);                
        set_skill("beiming-shengong", 550);     
        set_skill("dodge", 550);                
        set_skill("lingbo-weibu", 550);         
        set_skill("parry", 500);
        set_skill("finger", 500);
        set_skill("yiyang-zhi", 550);
        set_skill("liumai-shenjian", 200);
        map_skill("parry", "yiyang-zhi");
        map_skill("finger", "yiyang-zhi");
        map_skill("force", "beiming-shengong");
        map_skill("dodge", "lingbo-weibu");


		set("env/liumai","shenjian");
        set("chat_chance_combat", 100);
        set("chat_msg_combat",({ 
                (: exert_function, "beiming" :),
				(: perform_action, "dodge.luoshen" :),

                (: perform_action, "finger.yizhisanmai" :),
                (: perform_action, "finger.ciqu" :),
				//(: perform_action, "finger.liumai" :),
				(: perform_action, "finger.ciqu" :),
        }));

        setup();        
}
void init()
{
	object me;
	me = this_player();
	::init();
	if (interactive(me) && living(me) 
		&& !me->query_condition("killer")
		&& me->query(QUESTDIR1+"start") ) {
		me->start_busy(2);
        remove_call_out("greeting"); 
		call_out("greeting",2,me);
	} 
}
/*
void greeting(object me)
{
	if(!me) return;
	if(environment(this_object())!=environment(me)) return;

	if(!me->query_condition("killer")&&me->query(QUESTDIR1+"start") 
			&& !me->query_temp(QUESTDIR1+"see_duanyu1")
			&& !me->query_temp(QUESTDIR1+"see_duanyu2")
			&& !me->query(QUESTDIR1+"wuliangover")
			&& me->query_temp(QUESTDIR1+"jianying"))
    {
		//����
		  message_vision(HIC"\n$Nһת����һ����ȴ��������ȴ��һ������վ������ǰ���ճյĴ����ţ��Ǳ��龹Ȼ�ɰ��������ɾ��ɳա�\n"NOR, me);  
		  log_file("quest/TLBB", sprintf("%s(%s) �貨΢�������������������飺%d��\n", me->name(1),me->query("id"), me->query("combat_exp")) );
		  me->set_temp(QUESTDIR1+"see_duanyu2",1);
		  me->start_busy(1);
		  command("crazy");
		  command("say");
    }
	
	if(!me->query_condition("killer")
		&& me->query(QUESTDIR2+"start") 
		&& me->query_temp(QUESTDIR2+"pushdown") 
		&& !me->query(QUESTDIR2+"over"))
    {
		  message_vision(HIC"\n$N�������ң�����һ���������ӣ�����������ض����㿴���о�����һ�㱻���������ӡ�\n\n"NOR, me);                      
		  command("ah "+me->query("id"));
		  command("look "+me->query("id"));
		  command("heng");
		  command("say");
		  command("say �����˲���ò�࣬��ħɮ����һ����ɮ��ȴ��Ϊ����������"); 
		  me->start_busy(1);
    }
}*/

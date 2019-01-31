// shizhongyu.c ʯ����
//by kingso 2010 08 ������ϵ��

#include <ansi.h>
inherit NPC;

string ask_name();
string ask_dingdang();

string ask_jiuyuan();
string ask_changle();
string ask_huigui();
string ask_weihe();

#define XKX_QUEST1 "quest/������/Ħ����/"


void create()
{
        set_name("ʯ����", ({ "shi zhongyu", "shi", "zhongyu" }));
        set("gender", "����");
        set("age", 20);
        set("str", 15);
        set("int", 45);
        set("con", 18);
        set("dex", 20);
        set("per", 30);
        set("long", "����һ�����ṫ�ӣ���Լ��ʮ�����꣬��������֮�£�ɫ�紺��
֮�����������ã�ü��ī�������������������ﲨ����ŭ��ʱЦ�����Ӷ����顣\n");
        set("combat_exp", 5400000);
        set("shen_type", 1);
        set("attitude", "peaceful");

        set_skill("unarmed", 350);
        set_skill("force", 350);
        set_skill("blade", 350);
        set_skill("dodge", 350);
        set_skill("parry", 350);
        set_skill("literate",100);

        set_skill("wuhu-duanmendao", 350);
        set_temp("apply/attack", 30);
        set_temp("apply/defense", 30);
        set_temp("apply/armor", 5);
        set_temp("apply/damage", 10);
        map_skill("blade", "wuhu-duanmendao");
		map_skill("parry", "wuhu-duanmendao");

        set("neili", 200);
        set("max_neili", 200);
        set("jiali", 20);
        set("inquiry", ([
                "����" :  (: ask_name :),
                "����"   : (: ask_dingdang :),  
                "��Ԯ" :  (: ask_jiuyuan :),

                "���ְ�" :  (: ask_changle :), 

                "�ع�" :  (: ask_huigui :),  
 
                "ԭ��" :  (: ask_weihe :),  

                "���͵�" : "��Ȫ�ݸ�����һ��С����\n",
 
                "ʯ����" : "������֪��˭��ʯ���죬����˭��.\n",


        ]) );
        set("chat_chance", 8);
        set("chat_msg", ({
                "\nʯ����˵��: ������������ѽ���Һ�����ѽ��\n",
                "\nʯ����̾��: Ҳ��֪���ҵĶ�����ô���ˡ�\n",
                "\nʯ����˵��: ��������Ǻö���...\n",
                "\nʯ����˵��: ����˭�ܰ���ɱ���������ͷ���ֵ���лл���ˣ�\n",

        }));
        setup();
        carry_object("/clone/weapon/gangdao")->wield();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver", 10);
}

void die()
{
        say("\nʯ����˵�����һ��и���Ըû�ˣ�ϣ�����ܰ����չ˶�����\n");

        message_vision("ʯ�����Ŷ��������֣����ˣ�\n", this_object());
        ::die();
}

string ask_name()
{
    object me;
    me=this_player();
   
   
   if (!me->query_temp(XKX_QUEST1+"agree"))
       return "�����ĸ��а���ƾ��Ҳ��֪���ҵ����֣���\n";

   if (me->query_temp(XKX_QUEST1+"name"))
       return "�㲻���Ѿ��ʹ���������ô��\n";

   if ((int)me->query("combat_exp") < 1200000)
       return "����������è�Ĺ���ʡʡ�ɣ�\n";

        command("say  �ǰ����Ҿ���ʯ����");
        command("noshame " + me->query("id"));
      //  command("say  ���������ҵ��𣿣�Ҫ������Ǹ�����ͷ��һ��ģ�");
      me->delete_temp(XKX_QUEST1+"agree");

	  me->set_temp(XKX_QUEST1+"name", 1);
        
}
string ask_dingdang()
{
    object me;
    me=this_player();
   
   
   if (!me->query_temp(XKX_QUEST1+"name"))
       return "�����ĸ��а���ƾ��Ҳ���ἰ���������֣���\n";

   if (me->query_temp(XKX_QUEST1+"dingdang"))
       return "�㲻���Ѿ��ʹ���������ô,�����������������еģ�\n";


        command("say ��Ȼ�Ƕ����������ģ�������ʲô�أ���");
        command("say  ���������ҵ��𣿣�Ҫ������Ǹ�����ͷ��һ��ģ�");
        me->delete_temp(XKX_QUEST1+"name");
		me->set_temp(XKX_QUEST1+"dingdang", 1);
        return "";
}

string ask_jiuyuan()
{
    object me;
    me=this_player();
   
   message_vision(HIY"$N˵������ʯ�����ã������ܶ��������ί�й�����Ԯ��ģ���\n"NOR,me);
   if (!me->query_temp(XKX_QUEST1+"dingdang"))
       return "ʯ������ܵ�����һ����ת����ȥ��\n";

   if (me->query_temp(XKX_QUEST1+"jiuyuan"))
       return "��~����������մ�������ô������һ�飿~~��\n";


        command("say  ������������ҵģ��Ƕ��������������İɣ���̫���ˣ������ڿ����뿪�������ʺ�ĵط��ˣ�");
        command("touch " + me->query("id"));
        
        me->set_temp(XKX_QUEST1+"jiuyuan", 1);
	return "��Ȼ�Ǿ������ģ��ǲ�������һ����ı�أ�\n";        
}
//
string ask_changle()
{
    object me;
    me=this_player();
   
   
   if (!me->query_temp(XKX_QUEST1+"jiuyuan"))
       return "�Ҳ������㣬��������ҵ������ģ���\n";

   if (me->query_temp(XKX_QUEST1+"changlebang"))
       return "��~~����մ���~~~~��\n";


   command("say  ʲô�����������֡����������");
   command("!!! " );
   command("say  л����л����л������������~������Ҫɱ�Ұ�����");
   me->set_temp(XKX_QUEST1+"changlebang", 1);
        
}

int accept_object(object who, object obj)
{
	
	if (obj->query("id")=="bangzhu ling" 
		//&& obj->query("name")=="������" 
	   // && who->query_temp(XKX_QUEST1+"start")
	    && who->query_temp(XKX_QUEST1+"changlebang")
	//	&& obj->query_temp(XKX_QUEST1+"start")
		&&obj->query("owner")==who->query("id"))
	{
		command("say �ţ���ö���Ƶ�����ģ�\n");
		command("say ���������ǳ��ְ��������ģ��ǲ��Ǳ���ʯ�������ģ� ");
		who->set_temp(XKX_QUEST1+"renke",1);
		destruct(obj);
		return 1;
	}
	
}

string ask_huigui()
{
    object me;
    me=this_player();
   
   
   if (!me->query_temp(XKX_QUEST1+"renke"))
       return "ʯ�������ж�����ǲ��ţ����ܵ�����һ����ת����ȥ��\n";

   if (me->query_temp(XKX_QUEST1+"huigui"))
       return "��~����ô�ַ�������~~~~~��\n";


        command("say  ��������������ܶ������У�Ӧ���������ѣ����������ѾͲ��Ầ���ˡ�");
        command("sigh " );
        command("say  ����Ĳ���س��ְ�Һò����ײ��ӳ����ġ�");
        command("say  ����û�뵽����������ô�೤�ְ��׷�����ܵ���·�ϱ�л�̿͵����Ǹ�ʲô�������֡���ץ����������ʺ�ĵط���");
        command("say  ��ֻ�����������һ���Ҳ���������ﰡ��");
		 me->set_temp(XKX_QUEST1+"huigui", 1);
        
}

string ask_weihe()
{
    object me;
    me=this_player();
   
   
   if (!me->query_temp(XKX_QUEST1+"huigui"))
       return "�Ҳ������㣬���ܵ�����һ����ת����ȥ��\n";

   if (me->query_temp(XKX_QUEST1+"weihe"))
       return "��~~������մ���~~~~��\n";

   if ((int)me->query("combat_exp") < 1000000)
       return "����������è�Ĺ���ʡʡ�ɣ�\n";

        command("say  ʵ��������ɡ�");
        command("sigh " );
        command("say  ���ְ�֮����Ҫ�ҵ����������Ǳ���ʯ�Ǹ���������ı��");
        command("say  ���밡������ʲô���ͣ����书��ô�Ҳû��������Щ��ı��ƣ�����ƾʲôҪ�ҵ����ǵİ�����");
        command("say  �տ�ʼ���һ���Ϊ�������ϻ��������ϵ��ڱ����ֺ����أ����������Ű���������Ҫ��������");
        command("say  �����Ҳ�֪�������������ǣ���ʵ��Ҫ�ҵ�ʱ��ȥ���Ǹ�ʲô���Ʒ����");
        command("say  �����Ʒ�������ʲô�����������Ҳ�֪������˵ÿʮ���и������͵��ĵط�����������λ���Ʒ����ʹ��");
        command("say  �������˰���ר�ŵ�һЩ�����ɴ���ɣ���������ƣ�˵ʲô����ȥ���͵����ͣ����������ľ�Ҫ���š�");
        command("say  ��ʮ��������ȥ����û��һ�������ġ���û�н����Ҳ���������ˡ�");
        command("say  ��˵���ⲻ�ǰ��ҵ��ɸ������ס��Ľ��������𣿡�");
        command("say  ����˵�����Ǿ��Բ�������ȥ�ģ�����");
        me->set_temp(XKX_QUEST1+"weihe", 1);
	call_out("do_mingbai",4+random(5),me);        
}

int do_mingbai(object me)
{
	message_vision(HIR"$N��������ʯ����Ľ�˵�������˲������飬��ͬʱҲ���������Ի��У�\n"NOR,me);
	message_vision(HIG"˭��ʯ���죿˭���ǹ����֣����д���ȥȷ�ϣ�\n"NOR,me);
	message_vision(HIM"��Ȼ�벻���ף����Ȳ�ȥ�룬����ɽ�Ȱ���������˵��\n"NOR,me);
	message_vision(HIC"\n\n���£�$N������ԥ����ʯ����˵�����������������뿪����ط���˵����\n"NOR,me);

	me->set_temp(XKX_QUEST1+"yihuo",1);
	return 1;
}

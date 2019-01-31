// dingdang.c ����
//by kingso 2010 08 ������ϵ��

#include <ansi.h>
inherit NPC;
string inquiry_yu();
string ask_yu();
string ask_jiejiu();
#define XKX_QUEST1 "quest/������/Ħ����/"

void create()
{
        set_name("����", ({ "ding dang","ding"}) );
        set("gender", "Ů��" );
        set("age", 18);
        set("long", "һ��ʮ�߰������Ů�����������ӣ�һ�Ź��������������ޡ�\n");
        set("shen_type", 1);
        set("combat_exp", 4500000);
        set("str", 28);
        set("dex", 22);
        set("con", 25);
        set("int", 35);
        set("per",30);
        set("attitude", "friendly");

        set("qi", 12000);
        set("max_qi", 12000);
        set("jing", 2000);
        set("max_jing", 2000);
		set("max_jingli", 4000);
        set("neili", 12000);
        set("max_neili", 12000);
        set("jiali", 150);

        set_skill("force", 350);
        set_skill("unarmed", 350);
        set_skill("parry", 350);
        set_skill("dodge", 350);
        set_skill("taiji-shengong", 350);
        set_skill("taiji-quan", 350);
        set_skill("tiyunzong", 350);

        map_skill("force","taiji-shengong");
        map_skill("cuff","taiji-quan");
        map_skill("parry","taiji-quan");
        map_skill("dodge","tiyunzong");
        prepare_skill("cuff","taiji-quan");

		set("chat_chance", 10);
        set("chat_msg", ({

                CYN"������߶��: Ҳ��֪���ҵ�����������ô���ˡ�\n"NOR,
                CYN"��������Ĩ�˰����ᡣ\n"NOR,
                CYN"����һ��ţ�˵��: ���У���Ҫ��Ħ���°��ҵ�����Ȼ�����\n"NOR,
                CYN"����̾�˿�����˵��: Ҫ����������ͺ��ˡ�\n"NOR,
        }));
        set("inquiry",([
                "ʯ����" :  (: ask_yu :),
                "���" : (: ask_jiejiu :),
                "Ħ����" : "ǰ������ɽ�����ˣ���ҪС��ѽ���Ǹ���ͷ���书��ǿѽ��",
                "������" : "��˵����ʯ�����������ҾͲ�֪���ˡ�",
        ]));
        setup();
        carry_object(ARMOR_D("changqun"))->wear();

        add_money("gold", 2);
}

string ask_yu()
{
		object me;
		me=this_player();
   
   
	   if (!me->query(XKX_QUEST1+"start"))
	   {
			command("say �Һ����ҵ�����!\n");
			return "���ء������ҵ����硣�����Һ�������������\n";
	   }
	   if (me->query_temp(XKX_QUEST1+"jiejiu"))
			return "���ء������Ҳ��Ǹ���˵���𣿻��ʣ��㷳��������\n";

	   if ((int)me->query_skill("force",1) < 500)
			return "����������è�Ĺ���ʡʡ�ɣ�\n";

        command("say  ������~~~�����类�Ǹ�����ͷץ��Ħ��������������ˡ�����������~~~��");
        command("cry " + me->query("id"));
        command("say  ��ô�찡Ҫ����취�Ⱦ����簡�������Ǹ�����ͷ������ͷ�书��ô�ߣ�Ħ���������ϲ�ȥ~��");
		command("say Ҫ������үү����үү���ҾͲ����ˣ�������ô�������أ�");
        me->set_temp(XKX_QUEST1+"askyu", 1);
        return "˭Ҫ�ǰ��Ҿ����ҵ����磬�Ҿ�һ���úñ�������\n";
}

string ask_jiejiu()
{
    object me;
    object ob;
    me=this_player();
   
   
   if (!me->query_temp(XKX_QUEST1+"askyu"))
       return "������ʲô�취�������������ϵ�ȥĦ���£���Ҳ�򲻹��Ǹ�����ͷ����\n";

   if (me->query_temp(XKX_QUEST1+"jiejiu"))
       return "�Ҳ��Ǹ���������ֻ������취�ˣ�\n";

   if ((int)me->query("combat_exp") < 1200000)
       return "����������è�Ĺ���ʡʡ�ɣ�\n";

   command("say  �ٶ��ˡ������а취�ˣ�");
   command("grin " + me->query("id"));
   command("whisper "+ me->query("id") +" �Ҹ���˵�ɣ����������ӡ�������Ȼ�򲻹��Ǹ�����ͷ���Ǿ�Ҫ��ȡ���԰ɣ�\n");
   command("whisper "+ me->query("id") +" ��Ȼ�򲻹����Ҿ���ȥ������ͷ���ߣ���ȥ������ò��ã�!!\n");
   command("whisper "+ me->query("id") +" �������Һò��ã���������!!\n");
   command("cry ");

 //  command("whisper "+ me->query("id") +" ��������һ���Ի�ɢ������ǰ������үү���ҷ����õģ�ҩ��ʮ��ǿ����ֻҪ����ȥһ��㣬��Ҫ��˯һ������!!\n");
 //  command("whisper "+ me->query("id") +" ����ȥ�󣬿�����л�̿ͣ��ȿ��������һ����ڸ����Ŀ����У�һ�����ͻ��ι�ȥ�ġ�\n");
   command("beg1 " + me->query("id"));
 //  ob = unew("/d/motianya/obj/mhs");
  // ob ->move(me);
 //  command("rumor ��˵"+ me->name(1)+ "�Ӷ�����������һ��"+ ob->name(1)+ "��");  
   me->set_temp(XKX_QUEST1+"jiejiu", 1);
   add_action("do_answer","answer");
   return "�������ˣ�\n";   
}

int do_answer(string arg)
{
	object me=this_player();
	if (!me->query_temp(XKX_QUEST1+"jiejiu"))
	{
		return notify_fail("��ò��ò�,Ϲ��Ӧʲô��");
	}

	if (!arg||arg!="yes")
	{
		
		return notify_fail("������ؾܾ��˶��������󣡶���������ޣ�ת���ȥ\n");
	}
	command("jump ");
	command("say ����̫���ˣ�������ô��������һ���ذ�����ͳ����ģ�\n");
	command("say ����ȥ������ͷ���ߣ���ֱ��ȥ�����磡Ȼ�������ڳ��ְ����\n");
	me->set_temp(XKX_QUEST1+"agree", 1);

	command("");
}

// suxingh.c
// shilling 97.2
#include <ansi.h>

inherit NPC;
//inherit F_MASTER;
int ask_zhenlong();

void create()
{
	set_name("���Ǻ�",({"su xinghe","su"}));
	set("gender", "����" );
	set("nickname", "�ϱ�����");
	set("shen_type", 0);
	set("class", "scholar");
	set("age",60);
	set("str", 35);
	set("con", 30);
	set("int", 45);
	set("dex", 35);
	set("per", 30);

	set("no_clean_up",1);

	set("long",
"���˾��Ǻųƴϱ����˵����Ǻӣ���˵�������Ʊ磬 \n"
"��һ�������е����ߣ��������书Ҳ��������֪��\n");

	set("combat_exp", 100000000);
	set("attitude", "peaceful");
	set("chat_chance", 1);

	set("max_qi", 18000);
	set("max_jing", 18000);
	set("neili", 25000);
	set("max_neili",18000);
	set("jiali", 200);

	set_skill("force", 580);
	set_skill("dodge", 580);
	set_skill("parry", 580);
	set_skill("blade", 580);
  set_skill("qingyun-shou", 550);
	set_skill("beiming-shengong", 580);
	set_skill("ruyi-dao", 580);
	set_skill("liuyang-zhang", 580);
	set_skill("zhemei-shou", 580);
	set_skill("literate", 500);
	set_skill("piaomiao-shenfa", 580);
	set_skill("hand", 580);
	set_skill("strike", 580);
	set_skill("art", 220);
	set_skill("medicine", 220);

	map_skill("strike", "liuyang-zhang");
	map_skill("parry", "ruyi-dao");
	map_skill("blade", "ruyi-dao");
	map_skill("dodge", "piaomiao-shenfa");
	map_skill("force", "beiming-shengong");
	map_skill("hand", "zhemei-shou");
	prepare_skill("hand","zhemei-shou");
	prepare_skill("strike","liuyang-zhang");	
	set("chat_chance_combat", 90);  
	set("chat_msg_combat", ({
                (: perform_action, "blade.wanshi" :),
                (: perform_action, "blade.ruyi" :),
           
	}) );

	create_family("��ң��", 2, "����");
	set("title","��ң�ɵڶ��������");
	set("inquiry", ([
                "������" :  "����ʦ�ܱ���ʦ�ţ�������ʦ����л�������Ҵ���޷����֡����±���һ��ѳʦ��������ʦ���и���Ըδ�ˣ������������ƽ⣬����Ҳ�Ѽ�ʦ��֮�棬��������͵��������������Щ��������������ʦ��֮Լ�����Բ�������Լ������������ˣ����������յĵ��ӣ�Ҳ��ǿ�����������������ӡ�������ʮ������һ�����ɣ������֣����������ܹ��ƽ⡣��\n",                
                "�������": (: ask_zhenlong :),

        ]));
	
	
	
	
	setup();
	carry_object(__DIR__"obj/cloth")->wear();
	carry_object(__DIR__"obj/blade")->wield();
}


void attempt_apprentice(object ob)
{
	
	if (!QUEST_D->queryquest(ob,"xiaoyao/zhenlong")) 
	{
		command("say ��������ң����Ҫ�Ƚ⿪������֡�"); 
		return;
	}
	
	if ((int)ob->query_skill("beiming-shengong", 1) < 100) {
		command("say ����ң���ڹ���ԴȪ�����ڱ�ڤ�񹦵��ķ���"); 
		command("say " + RANK_D->query_respect(ob) + 
			"�ı�ڤ���Ƿ�Ӧ��������߰���");
		return;
	}
	
if ((string)ob->query("gender")=="����")
   {
		message_vision("���ǺӴ�Ŀ��˼Ƭ��, ˵�������ð�, �Ҿ��������ˡ���\n",ob);
       command("recruit " + ob->query("id"));
       ob->set("title", "��ң�ɵ���������");
       return;}
   else
      {
		message_vision("����ң�ɴӲ���Ů��֮��?��\n",ob);
       return;}
 }
 
 
 int ask_zhenlong()
{
	object me=this_player();
//��һ��Ҫ�����ԣ���ò�ϼ�	

if (QUEST_D->queryquest(me,"xiaoyao/zhenlong"))
{
	 command("say ԭ�����ƽ��������֮�����ˣ�");
	  return 1;
}

  if(QUEST_D->queryquesttime(me,"xiaoyao/zhenlong"))		
   	{
	  command("say �㻹��ȥ��Ϣһ�°ɣ���������ֲ�����");
	  return 1;
	}

	if (me->query("gender")=="����")
	{
		if( me->query("combat_exp")<20000000)
	     {
	        command("say �㹦��̫ǳ�ˣ�������ȥ�ɡ�");
	        return 1;
	     }
		 
		if (me->query("per") < 28) 
		{
			command("sigh ");
			command("say ����òǷ�ѣ����ǲ��У����м���и�ϵ�����и�ϵ������");
			return 1;
		}
		if (me->query_temp("xiaoyao/zhenlong/step1"))
		{
			command("say ���Ѿ��ʹ��ˡ�");
			return 1;
		}
	   me->set_temp("xiaoyao/zhenlong/step1",1);//�õ������һ���ı��
      command("say ��������硯��ǣ���쳣�ش�������úõ�����һ�ƣ������ƽ�ÿ�������һ���������¡�");
	  return 1;
	}
	else
		return 0;	
}


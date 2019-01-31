// Modify By River 98/12
#include <ansi.h>

inherit NPC;
string ask_duan();

void create()
{
        set_name("��ü����", ({ "huangmei heshang", "heshang", "huangmei" }) );
        set("title", "�黨������");
		set("nickname",HIY"��üɮ"NOR);
        set("gender", "����" );
        set("age", 65);
        set("str", 35);
        set("con", 30);
        set("dex", 23);
        set("int", 20);
        set("unique", 1);

        set("max_qi", 25000);
        set("max_jing", 5000);
        set("eff_jingli", 5000);
        set("max_neili", 25000);
        set("jiali", 200);       

        create_family("��������������", 10, "����");
        set("long", 
        "һ���������ơ����θߴ����ɮ������ɮ�������Ƴ�ü��üβ�´���\n");

        set("combat_exp", 10000000);
        set("score", 20000);       
	
        set_skill("parry", 500);
        set_skill("dodge", 500);
        set_skill("force", 450);
        set_skill("finger", 450);
        set_skill("buddhism", 200);
        set_skill("literate", 220);
        set_skill("yijin-jing", 450);
        set_skill("nianhua-zhi", 450);
        set_skill("shaolin-shenfa", 450);
        map_skill("dodge", "shaolin-shenfa");
        map_skill("parry", "nianhua-zhi");
        map_skill("finger", "nianhua-zhi");
        map_skill("force", "yijin-jing");
        prepare_skill("finger","nianhua-zhi");      
		set("inquiry", ([
			//"����" : (: ask_duan :),
			"����" : (: ask_duan :),       
		]));
		set("chat_chance_combat", 60);
		set("chat_msg_combat",({
			(: perform_action, "finger.fuxue" :),
			(: exert_function, "jingang" :),
		}));

        setup();
        carry_object("/d/shaolin/obj/cheng-cloth")->wear();
}


string ask_duan()
{
      object me=this_player();
	  message_vision(HIC"\n\n$N�Ϲ����üɮ˵��������ʦ���ã���ү�������˸����Ӹ����š���\n\n"NOR,me);
	  
	  if (!me->query_temp("yyzhi/four/fightok"))
		return "�����������������ϻ��������������ޡ�\n";
	  else {
	     me->set_temp("yyzhi/four/askhuang",1);
		 me->delete_temp("yyzhi/four/fightok");
         command("say ��Ȼ�Ƕ���ү���룬���������������⣿\n");
		 command("say Ҳ�գ�ȥ��Ϊ�������飬��ȥһ���˰������ɮ��Ҳ���Ǳ�����ϵĻʶ��ˡ�\n");
		 command("say ���ȥ����ү˵������˵��ʱ��ɮһ���ᵽ��\n");
		 return "��üɮ˵��ƫ��ͷ��˼����Ҳ�����";
        
	  }
	  
}

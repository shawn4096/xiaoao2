// youtanzhi.c ��̹֮
// Update by sohu@xojh
#include <ansi.h>

inherit NPC;
//inherit F_MASTER;

string ask_azi();
string ask_bingcan();
string ask_duzhang();

void create()
{
        set_name("��̹֮", ({ "you tanzhi", "you", "tanzhi"}));
        set("nickname", "����");
        set("long", "һ��������ͷ��ߵĹ��ˣ�����������һ����������ס���������Ǻ��ˡ�\n");
        set("gender", "����");
        set("age", 32);
        set("attitude", "peaceful");
        //set("env/wimpy", 100);
//	set("apprentice", 1);

        set("str", 35);
        set("int", 20);
        set("per", 10);
        set("con", 35);
        set("dex", 24);

        set("max_qi", 39000);
		set("qi",39000);
        set("max_jing", 6200);
		set("jing", 6200);
		set("max_jingli",7000);
		set("eff_jingli", 7000);
		set("quest/xx/csz/bingcan/pass",1);
		//set("jingli", 5000);
		set("max_neili",50000);
		set("neili",50000);
        set("jiali", 250);
        set("combat_exp", 15200000);
        set("shen", -2000000);

        set_skill("force", 550);
        set_skill("huagong-dafa", 550);
        set_skill("dodge", 450);
        set_skill("zhaixingshu", 450);
        set_skill("strike", 450);
        set_skill("chousui-zhang", 520);
        set_skill("parry", 500);
        set_skill("poison", 220);
        set_skill("literate", 180);
        set_skill("claw", 450);
        set_skill("sanyin-zhua", 450);

        map_skill("claw", "sanyin-zhua");
        map_skill("force", "huagong-dafa");
        map_skill("dodge", "zhaixingshu");
        map_skill("strike", "chousui-zhang");
        map_skill("parry", "chousui-zhang");
        prepare_skill("claw", "sanyin-zhua");
        prepare_skill("strike", "chousui-zhang");

        create_family("������", 2, "����");

        set("inquiry", ([
             	"����" : (: ask_azi:),
				"����" : (: ask_bingcan:),
				"���϶���" : (: ask_duzhang:),
        ]));
		set("chat_chance_combat", 80);
		set("chat_msg_combat", ({
			(: exert_function, "huadu" :),
			(: perform_action, "strike.chousui" :),
			(: perform_action, "strike.bingcan" :),
			(: perform_action, "strike.huoqiang" :),
			(: perform_action, "claw.wugong" :),
		}));
        setup();
		carry_object(ARMOR_D("baihu-qiu"))->wear();
}


string ask_azi()
{
	if (!this_player()->query_temp("bingcan/asktietou"))
	{
		command("say ��ͷ���ң��������������ɶ��\n");
		return "����ɵ��㶵ǵ�һ������ɵ��\n";
	}
	command("say ��Ȼ�ǰ��Ϲ����������ģ�����������ʲô!\n");
	command("sigh ");
	command("say �ұ����������£��κ������չ�����\n");
	this_player()->set_temp("bingcan/askazi",1);
	return "�������ˣ������ǰ��Ϲ�����������Ҫ����ȥ���Ǳ���ȥ�ˣ�\n";
}
string ask_bingcan()
{
	if (!this_player()->query_temp("bingcan/askazi"))
	{
		command("say �Ҳ���ʶ�㣬�������������ɶ��\n");
		return "һ���������Ƕ���\n";
	}
	command("say �������Ҳ��֪�����Ķ��ҵ����ϴ��Ǹ��������Ҵ������»۾������Ķ�͵���ģ�\n");
	command("blush ");
	command("say ���������������Ϣ�������ȥ����Ѱ�һ۾�����ѯ�ʣ�\n");
	this_player()->set_temp("bingcan/askbingcan",1);
	return "�۾������������½���԰�ӣ���ȥѰ�ҿ�����\n";
}
string ask_duzhang()
{
	object me=this_player();
	if (me->is_busy())
	{
		return "������æµ�У�\n";
	}
	if (!me->query("quest/xx/csz/bingcan/over"))
	{
		command("heng "+me->query("id"));
		command("consider ");
		command("say �������㾭����ͨ���Ҽ�������������������϶��ƣ���Ҳ�ᱻ������\n");
		command("say ֻҪ���ͨ���㾭�����ֿܵ������ĺ����������Ҵ���\n");
		return "�ߣ�";
	}
	if (me->query_skill("huagong-dafa",1)<450)
	{
		command("say ��Ļ����󷨹���̫��������450���ֿ���ס�⺮����Ϯ\n");
		return "�ߣ�";
	}
	if (me->query("con")<40)
	{
		command("say ����������̫��������40���ֿ���ס�⺮����Ϯ\n");
		return "�ߣ�";
	}
	
	if (me->query_skill("poison",1)<200)
	{
		command("say ��Ķ��Ʋ���200,̫�����ֿ���ס�⺮����Ϯ\n");
		return "�ߣ�";
	}
	if (time()-me->query("quest/xx/csz/bingcan/time")<86400)
	{
		command("say ������̫Ƶ���ˣ��������࣬�����岻�ˡ�\n");
		return "�ߣ�";
	}
	if (me->query("quest/xx/csz/bingcan/pass"))
	{
		me->set("title",HBWHT+HIG"���϶����洫"NOR);
		me->set("mytitle/quest/bingcan2title",HBWHT+HIG"���϶����洫"NOR);
		command("say ���Ѿ��⿪����϶��Ƶİ����ˣ���ʲô��Ц\n");
		return "�ߣ�";
	}
	message_vision(HIC"$n��$NЦ�������ϴθ��ҵ��������ϣ����Ѿ��ŵ��������ˣ����Լ�ȥ�����ɡ�˵��ͽ���$Nһ�������͡�\n"NOR,me,this_object());
	command("say ����϶���ʵûʲô���˵ģ���Ȼ���Ѿ���ͨ�����㾭�������ֿܵ�������������Ҿ͸��������޳ɱ��϶��Ƶİ��ذ�!\n");
	command("say ��������㡣������");
	command("whisper "+me->query("id"));
	me->start_busy(99);
	remove_call_out("thinking");
	call_out("thinking",1,me);
	return "���϶��Ʋ������ˣ����㶡������Ƿ壬��Ҳ���壡\n";
}

int thinking(object me)
{
	int i,j,total;
	if(!me) return 0;
	
	if(me->query_temp("bingcan_ask")<(10+random(3)))
    { 
	  me->add_temp("bingcan_ask",1);
      if(random(2)) tell_object(me,HIG"\n����������Ÿղ���̹֮��������ĵ����...\n"NOR);
             else tell_object(me,HIW"\nͻȻ�䣬һ�ɺ���������ľ��������һ�㴩��..\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"�ƺ���˼����ʲô��üͷ���塣\n"NOR, ({}));
	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);
	}
   else
   {  
	  me->delete_temp("bingcan_ask");
      total = me->query("con");
      j = 20;
      if(me->query("m-card-vip")) j =  18;
      if(me->query("y-card-vip")) j =  16;
      if(me->query("buyvip"))     j =  12;
	  i= random(j);
 
 
	  if( i<3 
		  && random(total)>40
		  && random(me->query("kar"))>28)
	  {
		tell_object(me,HIB"\n�㰴����̹֮��ָ�㣬�Ա��϶��Ƶ����������ƺ���Щ�ĵá�\n"NOR);
        tell_object(me, HIW"�㰴����̹֮���ԣ���Ϣ���ԡ���ǿѨ������������ᡢ���ء����š�����\n+"+
"��Ѩ��һ·���ż�׵�������ߵĶ��Ǳ��϶��θ���ҪѨ��Ȼ���Ǽ��С����ࡢ������������\n"+
"��̨��������������յ�����׵�����š��縮���Ի���ǿ�䡢�󶥡��������ŵġ��ٻ�Ѩ����\n"NOR);
		tell_object(me,HBGRN+HIW"\n������ǧ����࣬���ڵó���Ը�������϶����ڻ��ͨ��\n��ϲ�㣡Ц������ȥ��!\n"NOR);
       	//me->improve_skill("wuxiang-zhi", 10+random(me->query_int()));
		command("look "+me->query("id"));
		command("pat "+me->query("id"));
		command("haha "+me->query("id"));
		me->set("quest/xx/csz/bingcan/pass",1);
		me->set("title",HBWHT+HIG"���϶����洫"NOR);
		me->set("mytitle/quest/bingcan2title",HBWHT+HIG"���϶����洫"NOR);
		me->start_busy(1);
		log_file("quest/xxbingcan", sprintf("%8s(%8s) ʧ��%d�κ󣬳���������϶��Ƶľ�����iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"), me->query("quest/xx/csz/bingcan/fail"),i,me->query("combat_exp")) );
	 }
	 else
	 {
		me->add("quest/xx/csz/bingcan/fail",1);
		me->set("quest/xx/csz/bingcan/time",time());
		command("heng ");
		tell_object(me,HBBLU+HIW"\n��������̹֮��ָ�㣬��Ȼ�����˱��϶��Ƶİ��أ����ǶԱ��϶��ƹ�����������ȫȻ����Ҫ�졣\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->start_busy(1);
		log_file("quest/xxbingcan", sprintf("%8s(%8s) ���϶��ƽ���ʧ��%d�Ρ�iȡֵ��%d|���飺%d��\n", me->name(1),me->query("id"),me->query("quest/xx/csz/bingcan/fail"),i,me->query("combat_exp")) );
	  }
    	return 1;
  }

}

//��󡹦����Quest by server
//by spiderii@ty ����HAMA1���Ѷ���ߡ�����ȡ��3�λ�������ơ�expÿ����1M���µõ�һ�λ��ᣡ
//����rebootע��ID���Ѷ��ٴν��ͣ�server�ܱ�̬�����1����Ū�ˡ����3����ô�ѡ�tsk
#include <ansi.h>;
inherit NPC;
inherit F_MASTER;
int do_chi(string arg);
int do_chaikai();

void create()
{
        set_name("���߹�", ({"hong qigong", "hong", "qigong"}));
        set("nickname", "��ָ��ؤ");
        set("gender", "����");
        set("age", 75);
        set("long", 
"��һ�ų����������΢�룬���ִ�ţ������·���һ����һ��Ĵ����˲�����
ȴϴ�øɸɾ��������ϸ��Ÿ������Ĵ��«��\n");
        set("attitude", "peaceful");
        
        set("str", 35);
        set("int", 24);
        set("con", 30);
        set("dex", 30);

        set("rank", 10);
        set("max_qi", 58000);
        set("max_jing", 8000);
		set("max_jingli", 9000);
        set("neili", 55000);
        set("max_neili", 55000);
        set("jiali", 250);
        
        set("combat_exp", 15600000);
        set("score", 200000);
        set("death_times",380);

        set_skill("force", 550);             // �����ڹ�
        set_skill("huntian-qigong", 550);    // ��������
        set_skill("strike", 550);            // �����Ʒ�
        set_skill("xianglong-zhang", 550);   // ����ʮ����
       // set_skill("hand", 550);              // �����ַ�
        set_skill("dodge", 550);             // ��������
        set_skill("xiaoyaoyou", 550);        // ��ң��
        set_skill("parry", 550);             // �����м�
        set_skill("stick", 560);             // ��������
        set_skill("dagou-bang", 560);        // �򹷰���
        set_skill("begging", 200);           // �л�����
        set_skill("checking", 200);          // ����;˵

        map_skill("force", "huntian-qigong");
        map_skill("strike","xianglong-zhang");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("parry", "dagou-bang");
        map_skill("stick", "dagou-bang");
        
        prepare_skill("strike", "xianglong-zhang");

        create_family("ؤ��", 17, "ǰ����");
        setup();
		call_out("dest", 900, this_object());    
        
                carry_object(ARMOR_D("bainayi"))->wear();
                carry_object(ARMOR_D("shoes"))->wear();
                carry_object("/kungfu/class/gaibang/obj/gb_budai10")->wear();
				carry_object("/clone/weapon/zhubang")->wield();


}
void init()
{
        object ob;
        
        ob = this_player();
        if (interactive(ob) && !is_fighting() && !ob->query("questwg"))
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}
void greeting(object me)
{
		  tell_object(me,HIW"���߹������:���������Ҳ��ᣬ���������˵ ��\n\n"NOR);
		  tell_object(me,HIW"���߹�֧����������һ��ѩˮ���ִ�һ�����ʯ�ߵ��������ڳ�һֻ����������\n\n"NOR);
		  tell_object(me,HIW"��������ѩ����ӳ���Ƶ÷�����ֻ��������ҧ���˰������߰˴糤�Ĵ���򼣬��ڡ�\n\n"NOR);
		  tell_object(me,HIW"��䣬���ư�쵣�����������������߹���ס���β�ͣ�һ���������ڹ��\n\n"NOR);
		  tell_object(me,HIR"\n\n��Щ�������һ�󣬱㶼�������ˡ�\n\n"NOR);
		  tell_object(me,HIY"\n\n���߹��������͹��������ȥ��ը��΢��֮��������ϰ��ȣ��������������ˡ�\n\n"NOR);
		  tell_object(me,HIY"һ������������У�������˼���������΢�գ�̾��һ������ֻ������֮���֡�\n\n"NOR);
		  tell_object(me,HIY"�����ڴ��ӡ�\n\n"NOR);
		  tell_object(me,HIG"\n\n���߹�����ʮ�����Ժ���������Ҽ�������Ӣ�ۺú���ɱͷ��Ѫ������ü��\n\n"NOR);
		  tell_object(me,HIG"ͷ��ȴûһ���Ҹ����Ͻл���һ����򼡣С���ޣ���Ҳ��ҳԣ�chi������\n\n"NOR);
        
          add_action("do_chi","chi");
        
          return;
}
void dest()
{
	object me,ob;
	ob = this_player();
	me = this_object();

	//write(me->query("name")+"��üһ�������´β�Ҫ�����������㡣\n",me);  
	write(me->query("name")+"һ��ת��Ʈ����ȥ��\n",me);  

	destruct(this_object());
}
int do_chi(string arg)
{
        object me=this_player();
        object ob=this_object();
        if (!arg)
        return notify_fail(HIW"��Ҫ��ʲô��\n"NOR);
        if (arg == "wugong")
        {
                remove_action("do_chi","chi");

			tell_object(me,HIC"\n\n�㽫һ�������ڿ���һ����ֻһ������ȥ�����������������ִ����㣬����\n\n"NOR);
			tell_object(me,HIC"��Ũ��һ��֮�д�δ���������ζ���ٽ��˼��ڣ�һ��µ������ȥ����ȥЮ�ڡ�\n\n"NOR);
			tell_object(me,HIC"�������ԣ����ޣ�������\n\n"NOR);
			call_out("feng_out",5,ob,me);
        }
        else 
        return notify_fail(HIW"û������������\n"NOR);

        return 1;

}
void feng_out(object hong,object me)
{
        object feng;
		object fbroom;
        if (!objectp(feng=present("ouyang feng",environment(me))))
        {
			if (me->query_temp("fbroom")) 
			{
				
			fbroom=me->query_temp("fbroom");			
			feng = new ("/d/huashan/hamasuperquest/feng");
			feng->move(fbroom);
			}
			else
			{
				tell_object(me,HIR"\n\n������Ϣ��ʧ�������޷�������\n\n"NOR);
				return;
				
			}
						
        }

		tell_object(me,HIR"\n\n���������Ҷ�Ե���������ֻ���졢�졢�켸���죬ɽ�Ǻ�ת����һ�ˣ���\n\n"NOR);
		tell_object(me,HIR"�ӵߵ���˫�ָ���ʯ�飬�ŵض��У���������ŷ���档ŷ���������˵����顣\n\n"NOR);
		tell_object(me,HIR"�߹����𹥻�����ʽ���죬�ߴ�ߺ�������һ������������������ɣ���\n\n"NOR);
        feng->kill_ob(hong);
		//hong->kill_ob(feng);
        call_out("chai_out",10,hong,feng,me);

}



void chai_out(object hong,object feng,object me)
{        
    //feng->remove_all_killer();
	tell_object(me,HIC"\n\nŷ����ͻȻ���������ȣ�˫��һ�䣬�������������һ����У������󡡣\n\n"NOR);
	tell_object(me,HIC"��������˫���뷢����ǰ�Ƴ�����һ��ʵ������������֮���ۡ����߹��;�����\n\n"NOR);
	tell_object(me,HIC"����������֪���Ҳ��˫����ǰƽ�ơ���һ������Ӳ��Ӳ��ɲ��֮�䣬���¡�\n\n"NOR);
	tell_object(me,HIC"�ﾹȻ��ס������\n\n"NOR);
	tell_object(me,HIR"\n\n���˽���һ�ᣬŷ����ͷ��͸��һ���Ƶİ���������Խ��ԽŨ����������һ�㡣\n\n"NOR);
	tell_object(me,HIR"���߹�Ҳ��ȫ�����������ۼ�������ɫ��䣬�������������յ�һʱ���̣��ǡ�\n\n"NOR);
	tell_object(me,HIR"ͬ���ھ����ɣ�������ǰ�𿪣�chaikai�����Լ��������������̫Զ ����롣\n\n"NOR);
	tell_object(me,HIR"�ֽⲻ�������������Լ�һ��������\n\n"NOR);
    me->set_temp("hschaikai",1);
	  //  add_action("do_chaikai","chaikai");
        //call_out("chaikai_out",8,hong,feng,me);
}

void all_dest(object feng,object hong)
{
        destruct(feng);
        destruct(hong);

}

int hong_say()
{
	object me=this_player();
	command("look "+me->query("id"));
	if (me->query("family/master_master")=="���߹�")
	{
		command("say �ҵ���˭��ԭ�����ҵĹ�ͽ��"+me->query("name")+"������Ȼ�����ˣ������Ҵ��㼸�У���ѵ��ѵ���϶��\n");

	}
	else {
		command("say �ҵ���˭��ԭ����"+me->query("family/master_name")+"͵͵�̵ĺõ��Ӱ����������ǲ���\n");
		command("thumb "+me->query("id"));
	}
	command("say ������С���޻����������ҵ�����ô�����\n");
	command("say ���϶�����Ҿ�����һ�����������ڹ����ޣ��������ľͰ���ʩչ����������ʽ\n");
	command("say �򹷰���ʹ�������޹���\n");
	command("hehe");
	command("say ����Ը������� answer Ը�� ,����Ը��������\n");
	add_action("do_answer","answer");

}
int do_answer(string arg)
{
	object me=this_player();
	if (!arg||arg!="Ը��")
	{
		command("kick "+me->query("id"));
		return 1;
	}
	message_vision(HIC"$N����˵��������Ը�⡱!"NOR,me);
	me->set_temp("wugou/answerok",1);
	return 1;
}
int hong_say2()
{
	object me=this_player();
	command("look "+me->query("id"));
	if (me->query("family/master_master")=="���߹�")
	{
		command("laugh ");
		command("pat "+me->query("id"));
		command("say "+me->query("name")+"��ͽ����������ϸ�����ˣ�\n");

	}
	else {
		command("say ��������"+me->query("name")+"С���ޣ����ҽ�ѵ��ѵ�����蹷��\n");
		command("thumb "+me->query("id"));
	}
	command("say �����޹���һ�䡸�����ӵ�ʩ���� �����˫ȮĪ��ͷ����\n");
	command("say �����޹��ڶ��䡸������ǽ��δ� �����������β����\n");
	command("say �����޹������䡸����Ϲ������У� ����ͷ�����ġ���\n");
	command("say ����������������������������������������������������\n");
	message_vision(HIY"\n\n$N������$N����ʽ���⣬���ڴ򹷰������հ�������Щ��֪��\n"NOR,me,this_object());
	command("hehe");
	command("say �϶���㿴����������ƽⰡ��\n");
	command("laugh ");
	//command("");
	//add_action("do_answer","answer");

}
int hong_say3()
{
	object me=this_player();
	command("look "+me->query("id"));
	
	command("laugh ");
	command("say �����������ؤ��򹷰������վ��������޹�����ͽ������ɿ�����ˣ�\n");
	command("say ���������ؤ��������֮һ��Ҳ�ǰ���������ϰ֮�似��\n");
	command("say ��ͽ�����ܷ�����Ϳ���ġ�\n");
	//me->set_temp("");
}
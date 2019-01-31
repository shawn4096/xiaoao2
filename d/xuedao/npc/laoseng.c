// laoseng.c Ѫ��������ɮ
// by sohu@xojh
#include <ansi.h>
inherit NPC;

string ask_bladebook();
string ask_miji();
string ask_gushi();
string ask_lansha();

void create()
{
	set_name("��ɮ", ({"lao seng","seng"}));
	set("long",
                "����Ѫ�������ʦ�ܣ�����������������������������ĺ��⣬һ˫�̶�С��\n"
                "���������ش�����,�����������������ȴ��Ϊ��׳��\n"
	);

    set("title", "Ѫ��������ʦ��");
	set("gender", "����");
	set("attitude", "peaceful");
	set("class", "huanxi");

	set("inquiry",([
		"������ȫ"	: (: ask_bladebook :),
		"Ѫ���ؼ�"	: (: ask_miji :),
		 "����"	: (: ask_gushi :),
		"��ɰ�־���"	: (: ask_lansha :),

	]));

	set("age", 30);
	set("shen_type", -1);
	set("str", 25);
	set("int", 15);
	set("con", 25);
	set("dex", 20);
	set("max_qi", 22450);
	set("eff_jing", 6200);
	set("max_jing", 6200);
	set("neili", 12500);
	set("max_neili", 12500);
	set("jiali", 200);
	set("combat_exp", 9300000);
	set("score", 1000);
	set("unique", 1);
	set("book1",1);
		set("book2",1);

	set_skill("force", 450);
	set_skill("xuedao-jing", 450);
	set_skill("dodge", 450);
	set_skill("xueying-dunxing", 450);
	set_skill("strike", 450);
	set_skill("hongsha-zhang", 450);
	set_skill("parry", 450);
	set_skill("huanxi-chan", 150);
	set_skill("literate", 230);
	set_skill("blade", 480);
	set_skill("xuedao-daofa", 480);
	set_skill("hand", 480);
	set_skill("lansha-shou", 480);
	set_skill("throwing", 480);

	map_skill("force", "xuedao-jing");
	map_skill("dodge", "xueying-dunxing");
	map_skill("strike", "hongsha-zhang");
	map_skill("parry", "xuedao-daofa");
	map_skill("blade", "xuedao-daofa");
	map_skill("throwing", "lansha-shou");

	prepare_skill("strike", "hongsha-zhang");

	create_family("Ѫ����", 4, "����ʦ��");
	
	setup();
    carry_object("clone/weapon/blade")->wear();
    carry_object("d/xuedao/obj/qinxiu-jiasha")->wear();
}
//��������book2

string ask_bladebook()
{
	object me,ob;

	me = this_player();

	if (me->query("family/family_name") != "Ѫ����")
		return RANK_D->query_respect(me) + "�����ڿ���Ц�ɡ�\n";

	if( me->query("class")!="huanxi" )
		return "�㲻����Ѫ���Ż�ϲ�����ӡ�\n";
	if( me->query_temp("asklaoseng/blade2"))
		return "�㷽�Ų����Ѿ��ù�һ����ô����\n";
	if( this_object()->query("book1")<1)
		return "�������˽��Ȿ������ȫ�����ˣ���\n";

	if( (string)me->query("gender") == "����" )
		return "ʩ�������ȱ����˵�����ն�������������Ѫ������ȫ�������⣬.����\n";

	if (me->query_skill("blade",1)<60)
		return "��Ŀǰ�Ļ�������ˮƽ̫�ͣ�����60����Ҫ������Ҳû�á�\n";
	if (present("daofa daquan",me))
		return RANK_D->query_respect(me) + "�����ϲ�����һ��ô��\n";
	if (present("daofa daquan",environment(me)))
		return RANK_D->query_respect(me) + "���ϲ�����һ��ô��\n";
	this_object()->add("book1",-1);
	me->set_temp("asklaoseng/blade2",1);
	ob=new("d/xuedao/obj/bladebasic_book");	
	ob->move(me);
	
	return "����������������ҾͰ��Ȿ���ɡ�������ȫ��������ģ�ǧ����Ū���ˡ�\n";
}
//��������book3

string ask_miji()
{
	object me,ob;

	me = this_player();

	if (me->query("family/family_name") != "Ѫ����")
		return RANK_D->query_respect(me) + "�����ڿ���Ц�ɡ�\n";
	if( me->query("class")!="huanxi" )
		return "�㲻����Ѫ���Ż�ϲ�����ӡ�\n";
	if( me->query_temp("asklaoseng/blade3"))
		return "�㷽�Ų����Ѿ��ù�һ����ô����\n";
	if( query("book2")<1)
		return "�������˽��Ȿ������ȫ�����ˣ���\n";
	if( (string)me->query("gender") == "����" )
		return "ʩ�������ȱ����˵�����ն�������������Ѫ������ȫ�������⣬.����\n";

	if (me->query_skill("blade",1)<120)
		return "��Ŀǰ�Ļ�������ˮƽ̫�ͣ�����120����Ҫ������Ҳû�á�\n";
	if (!me->query("quest/xd/dichuan"))
		return "��Ŀǰ���ǵմ����ӣ���ô���ܸ����Ȿ�顣\n";
	if (present("daofa jingyao",me))
		return RANK_D->query_respect(me) + "�����ϲ�����һ��ô��\n";
	if (present("daofa jingyao",environment(me)))
		return RANK_D->query_respect(me) + "���ϲ�����һ��ô��\n";
	this_object()->add("book2",-1);
	me->set_temp("asklaoseng/blade3",1);

	ob=new("d/xuedao/obj/blade_book");	
	ob->move(me);
	
	return "�Ȿ������Ѫ���ŵ�������ɵĵ��������ؼ���Ѫ��������Ҫ�������Ҫ�úñ��ܡ�\n";
}

string ask_gushi()
{
	object me,ob;

	me = this_player();

	if (me->query("family/family_name") != "Ѫ����")
		return RANK_D->query_respect(me) + "�����ڿ���Ц�ɡ�\n";
	if( me->query("class")!="huanxi" )
		return "�㲻����Ѫ���Ż�ϲ�����ӡ�\n";
	if (me->query_skill("force",1)<200)
	{
		return "��Ļ����ڹ���򲻵���������Ҳû��\n";
	}

	if (!me->query_temp("xd/laoseng/start"))
	{
		command("say ������������ҵĹ��£���Ҫ����ɮ�Ҷ�๩�\n");
		command("say ����ϲ������¶�����ˣ���������������Ҳ�У�\n");

		return "Ҫ�ǲ�Т���ң��ͱ��������ң�û������Ǳ��ô����\n";
	}
	command("say ���������ʱ��ϲ�����ڴ��һ�����\n");
	command("say ���Ǿ���һ����ˣ��һ�����֣���ʱ������ĵ����ӡ�\n");
	command("say ��������������һ����Կ����ˡ�\n");
	command("say ���趨��ı�����ݺ���Ȼ��Ͱ��ҹ�Ѻ�ڴ��Ρ�\n");

	command("say �ҳ����������İ��Ĺ����Ѿ����Ǹ���԰�ռ�ˡ�\n");
	command("say �ҵķ���Ҳ�����ˡ�\n");

	command("say ���ʲ���������Ͱ��Ƕ�Եķ��Ӹ����ˡ�\n");
	command("say �����Ҿͱ�����һ�٣�����һϢ��������ˡ�\n");
	command("say �ҷ��Ĳ����˳��Ĳ�Ϊ�ˣ������и���ѧ�գ�����ڶ�����\n");
	command("say ���������ѧ������ɰ�֡�\n");

	command("say ѧ���гɺ���һֱ��ȥ���Ǹ����ȫ�Ҷ���ɱ�ˡ�\n");
	command("say �����Ǹ����ȫ��ɱ�ˡ�\n");
	command("say ����Ϊ��������һֱû����Ը��\n");
	command("say �����Ҿ͵�Ѫ���Ű�ʦѧ�ա�\n");
	command("say һֱ�����죬���Ĵ�ɡ�\n");

	me->set_temp("xd/laoseng/ask",1);

	return "����ɰ�ֿ��Ե��ַ�Ҳ���Է���������ʵ������\n";
}

string ask_lansha()
{
	object me,ob;

	me = this_player();
	if (time()-me->query("quest/xd/lansha/time")<86400)
	{
		//command("say ��");
		return "������̫Ƶ���ˣ��书��ɻ��������ꣿ��\n";
	}

	if (!me->query_temp("xd/laoseng/ask"))
	{
		return "����ϲ������¶�����ˣ���������������Ҳ�У���\n";
	}
	if (!me->query_temp("xd/laoseng/taskok"))
	{
		command("say ��Ȼ����ѧ���ž����������ȥ��ɽ�ѷ������Ǹ���Ը���ɱ�ˡ�\n");
		command("say ���ҳ���ڶ����ȡ�\n");
		me->set_temp("xd/laoseng/killfeng",1);
		return "��ȥ�ѷ����ϸ���ɱ�ˣ�������ڶ�������ƾʲô���㣿\n";
	}
	command("say ��ɮ����ʵΪ��е����ˣ�������ƽʱʱ��Т�����������Ӻ���¶���ӵķ���\n�Ҿʹ���������ɰ�־�����\n");
	call_out("study_lansha",1,me);
	return "������Ͼ��Ǹ���ԡ�\n";
}

int study_lansha(object me)
{
	
	int i,j; 
	if(!me) return 0;
	i=random(me->query("kar"));
	j=20;
	if(me->query("m-card-vip")) j =  18;
	if(me->query("y-card-vip")) j =  15;
	if(me->query("buyvip"))     j =  10;
	j=random(j);
	if (me->query("family/family_name")!="Ѫ����")
	{
		return notify_fail("�㲻��Ѫ���ŵ��ӣ�������ǲ��ô��\n");
	}

	if (me->query("quest/xd/lansha/pass"))
	{
		
		return notify_fail("���Ѿ��⿪��������⣬����Ե�޹���������������\n");
	}


	if (time()-me->query("quest/xd/lansha/time")<86400)
	{
		//command("say ��");
		return notify_fail( "������̫Ƶ���ˣ��书��ɻ��������ꣿ��\n");
	}
	if (!me->query("quest/xd/dichuan"))
	{
		//command("say ��");
		return notify_fail( "Ѫ����Ҫ����ʼ����һ���ҳϵ��ӣ���ǵմ������ܴ�����߼��书����\n");
	}
	if (me->query_skill("force",1)<200)
	{
		//command("say ��");
		return notify_fail("��ϰ�����ڹ���Ҫ��200������ϰ��ɰ�֣����Ǻú�����ȥ�ɣ���\n");
	}

	if (i>23
	  && j<5
	  && me->query("kar")<31)
 	{ 
        
         me->start_busy(3);
		 message_vision(HIB"\n$Nĥ�˰��죬������Ѩ��Ȼһʹ������ɰ�־����Ȼ��ͨ����\n"NOR,me); 
         message_vision(HIY"\n$N���д�ϲ�����������������Ц������˵������ԭ����ˣ�ԭ����ˡ���\n"NOR,me); 
         message_vision(HBYEL+HIW"\n$N����������ĥ��ϰ����������������ɮ�����ڵ���ɰ�ֵİ��أ���\n"NOR,me); 
         log_file("quest/xdlansha", sprintf("%s(%s) ��ɰ�ֽ��ܳɹ�����%d�β��򣬻�Ե�ɺ��£��ɹ�������ɰ�ּ��İ��أ��������ֵ��%d,��ǰ���ֵ��%d,��ǰ���飺%d,\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/xd/lansha/fail"),
		 i,
		 j,
         me->query("combat_exp"),
		 ));

		 me->set("quest/xd/lansha/time",time());
		 me->set("quest/xd/lansha/pass",1);
		 return 1;
     }
	 else {
	     message_vision(HIG"\n$N�����ɥ�����������˵��������������ɰ�����ǲ��ýⰡ������Ŭ���ɡ���\n"NOR,me); 
		 message_vision(HIY"\n������ɰ�־�������ʧ�ܣ�\n"NOR,me); 
         log_file("quest/xdlansha", sprintf("%s(%s) ʧ�ܣ�������ɰ�ֵ�%d��ʧ�ܣ��������ֵ��%d,��ǰ���ֵ��%d,��ǰ���飺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/xd/lansha/fail",1),
		 i,
		 j,
         me->query("combat_exp"),));        
		 me->add("quest/xd/lansha/fail",1);
		 me->set("quest/xd/lansha/time",time());
		 me->start_busy(2);
		 me->delete_temp("quest/xd/lansha/modao");
		 me->delete_temp("quest/xd");
		 return 1;
   }
	

}
	
int accept_object(object who,object obj)
{
	object obb;
	int i;
	i=who->query("quest/xd/xiaojing/times");
	
	if ((obj->query("id")=="wulu wan"||obj->query("id")=="wurou wan")
		&&obj->query("owner")==who->query("id"))
	{
		if (random(i)>200
			&&random(who->query("kar"))>20)
		{
			command("say �ҹ۲���þ��ˣ���������С���Ӳ���\n");
			command("say ��������һֱ�������ҹ���������ӣ�\n");
			command("say �����ҽ���ܸ��ˣ��͸��㽲���ҵĹ��£���Σ���\n");
			who->set_temp("xd/laoseng/start",1);
		}
		command("say �ܵõ����Т������ɮ�Һܿ���.\n");
		who->add("quest/xd/xiaojing/times",1);
		destruct(obj);
		return 1;

	}
	
	else if (who->query_temp("xd/laoseng/killfeng")
		&&objectp(obb=obj->query("kill_by"))
		&&obj->query("name")=="�����ϵ��׼�"
		&&obb->query("id")==who->query("id"))
	{
		command("haha "+who->query("id"));
		command("say ���ܽ�"+obj->query("victim_name")+"�����Ը���ɱ�ˣ��Һܸ��ˣ�\n");
		command("pat "+who->query("id"));
		command("say ��˵��������书���������Һܿ����㣡\n");
		destruct(obj);
		who->set_temp("xd/laoseng/taskok",1);
		return 1;
	}	
	command("say ���Ĳ���ʵ��������������Ȼ��ζ������ȱ��������������ɮ���Ƶ�Ч������\n");
	return 0;
	
}


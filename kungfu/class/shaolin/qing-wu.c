// Npc: /kungfu/class/shaolin/qing-wu.c
// Date: YZC 96/01/19
#include <ansi.h>

inherit NPC;
inherit F_MASTER;

int ask_job();
int ask_over();

void create()
{
	set_name("���ޱ���", ({
		"qingwu biqiu",
		"qingwu",
		"biqiu",
	}));
	set("long",
		"����һλ���ǿ����׳��ɮ�ˣ�����û���������ȫ���ƺ��̺�\n"
		"�������������һϮ�ײ��ڱ����ģ��ƺ������ա�\n"
	);


	set("gender", "����");
	set("attitude", "friendly");
	set("class", "bonze");
	set("title", "�Ӵ�ɮ��");

	set("age", 30);
	set("shen_type", 1);
	set("str", 23);
	set("int", 17);
	set("con", 20);
	set("dex", 24);
	set("max_qi", 350);
	set("max_jing", 200);
	set("neili", 350);
	set("max_neili", 350);
	set("jiali", 30);
	set("combat_exp", 50000);
	set("score", 100);

	set_skill("force", 60);
	set_skill("hunyuan-yiqi", 60);
	set_skill("dodge", 60);
	set_skill("shaolin-shenfa", 60);
	set_skill("hand", 60);
	set_skill("fengyun-shou", 60);
	set_skill("parry", 60);
	set_skill("buddhism", 60);
	set_skill("literate", 60);

	map_skill("force", "hunyuan-yiqi");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("hand", "fengyun-shou");
	map_skill("parry", "fengyun-shou");

    prepare_skill("hand", "fengyun-shou");

	create_family("������", 40, "����");
	set("inquiry", 
    ([
         "�幤" : (: ask_job :),
          "����" : (: ask_over :),
    ]));

	setup();

      //  carry_object("/d/shaolin/obj/jiedao")->wield();
        carry_object("/d/shaolin/obj/qing-cloth")->wear();
}

#include "/kungfu/class/shaolin/qing.h"


int ask_job()
{
	object me,shi,ob;

	me=this_player();
	if (me->query_temp("sljob/qingwu/askqingwu"))
	{	
		command("say ����Ե�޹ʲ�Ҫ����Ϸƶɮ��\n");
		command("say �Ҳ����Ѿ�������ȥ��"+me->query_temp("sljob/qingwu/jobname")+"��ô��������ȥ��\n");
		return 1;
	}
	if (me->query("gender")!="����")
	{	
		command("say ����Ե�޹ʲ�Ҫ����Ϸƶɮ��\n");
		command("say ���³���ֻ��ļ���ˣ�\n");
		return 1;
	}
	if (me->query("combat_exp")>500000)
	{	
		command("say ����˸ߵľ���ֵ�Ͳ�Ҫ�ڴ˻��ˣ�ȥ�ɵ��İɣ�\n");
		return 1;
	}
	if (me->query("family"))
	{	
		command("say ���Ѿ��������ɣ��ѵ�����뱾�¼�ϸ����\n");
		return 1;
	}
	if (me->query("shen")<0)
	{	
		command("say ��������ɷ֮�࣬������������\n");
		return 1;
	}
	if (me->query_condition("job_busy"))
	{	
		command("say ���������ڹ�����æ�У�������������\n");
		return 1;
	}


	if (me->is_busy()||me->is_fighting()||me->query_condition("job_busy"))
	{
		command("say ����������æ���У�����������\n");
		return 1;
	}
	message_vision(HIY"$N��$n���������Ϊ������Χ���������幤�����飬��Щ�ƾ٣�\n"NOR,me,this_object());
	command("say "+me->query("name")+"����Ȼ����������ľ�����Щ�幤�ɣ�\n");
	command("say �����������ڿ���\n");

	switch (random(2))
	{
		case 0:
			tell_object(me,"���ޱ���˵����"+me->query("name")+"�����ɽ���Ǵ�������˵���Ǻü���û���ˣ��㵽ɽ��С��ȥ������\n");
			tell_object(me,"���ޱ���˵�������Ǵ���������������Ҫ���ã���\n");
			command("say ���գ����գ�");
			me->set_temp("sljob/qingwu/weizhu",1);
			me->set_temp("sljob/qingwu/jobname","ι��");
			me->apply_condition("sljob_qingwu",10);
			break;
		case 1:
			tell_object(me,"���ޱ���˵����"+me->query("name")+"�������ɽ��������Ů�ܶ࣬�е�æ��������\n");
			tell_object(me,"���ޱ���˵�������Ȼ��Ϊ���������������ȥӭ��ͤ����ͨ���ʣ�\n");
			me->set_temp("sljob/qingwu/yingke",1);
			me->set_temp("sljob/qingwu/jobname","ӭ��");
			me->apply_condition("sljob_qingwu",10);
			ob=new("/d/shaolin/obj/yingke-ling");
			ob->set_temp("sljob/qingwu/yingke",1);
			ob->set("owner",me->query("id"));
			ob->move(me);
			tell_object(me,"���ޱ���˵�����Ҹ���һ�����ƣ��㵽��ɽ��ӭ��ͤ��ݸ����������Իᰲ�ţ�\n");
			command("say �����ӷ�");
		break;
		default:break;
	}
	tell_object(me,"��ȥ��أ���Ҳ��һ�ֿ��飡\n");
	return 1;
}

int ask_over()
{
	object me,ob;

	me=this_player();
	
	if (me->query_temp("sljob/qingwu/weizhuok"))
	{
		tell_object(me,me->query("name")+"����ɵĺܲ����Ǵ���˵��ι��ܾ��ģ��ܸ����治����ȥ��Ϣȥ�ɣ�\n");
		//me->set("job_name","���ִ���");

	}
	if (me->query_temp("sljob/qingwu/yingked"))
	{
		tell_object(me,me->query("name")+"����ɵĺܲ�������ʦ��˵�ˣ��㹤���ܸ����治����ȥ��Ϣȥ�ɣ�\n");
		//me->set("job_name","����ӭ��");

	}
	if (!me->query_temp("sljob/qingwu/weizhuok")&&!me->query_temp("sljob/qingwu/yingked"))
	{
		command("say ��û��Ҳû�£��´��ٿ�ʼһ��,��ͷ������\n");
		me->delete_temp("sljob");
		me->clear_condition("sl_yingke");

		me->add_busy(2);
		return 1;
	}
	me->set("job_name","���ִ���");

	me->apply_condition("job_busy",2);
	me->apply_condition("sljob_qingwu",3);
	if (me->query("combat_exp")<100000)
	{
		tell_object(me,"��������ƾ����к�ֵ�ó��ޣ������ӣ��Һܿ����㡣\n");
		TASKREWARD_D->get_reward(me,"���ִ���",1,0,0,1,0,0,0,"���ޱ���");  
	}else{
		tell_object(me,"���������Ʊ����úøɣ�ƶɮֻ�ܸ���Щ�����Ǳ�ܣ�\n");
		me->add("potential",10);
		me->add("shen",100);
	}
	
	if (random(me->query("job_time/���ִ���"))>200
		&&!me->query("quest/sl/chujia/pass")
		&&random(me->query("kar"))>25 )
	{			
		message_vision(HIG"���ޱ���΢Ц�ض�$N˫�ֺ�ʮ���������ӷ�ʩ���������Ļ۸������з�Ե������Ը��Ϊ�����³��ҵ��ӣ��ҿ��Ը����Ƽ�����\n"NOR,me);
		ob=new("/d/shaolin/obj/jujianxin");
		ob->set("owner",me->query("id"));
		ob->move(me);
		me->set("quest/sl/chujia/pass",1);
	}
	me->delete_temp("sljob");
	tell_object(me,"��ȥ��أ���Ҳ��һ�ֿ��飡\n");
	return 1;
}
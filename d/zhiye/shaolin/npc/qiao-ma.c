// lao-qiao.c ������

inherit NPC;
#include <ansi.h>
int ask_job();
int ask_over();

void create()
{
	set_name("�Ǵ���", ({ "qiao dama", "qiao" , "dama"}));
	set("gender", "Ů��");
	set("age", 55 );
	set("long",
		"���ǽ����ú������Ƿ塱��ĸ�ף���ɫ���飬�����׺͡�\n"
	);
	set_skill("unarmed", 20);
	set_skill("dodge", 20);
	set("qi", 400);
	set("max_qi", 400);
	set("eff_qi", 400);
	set("jing", 300);
	set("max_jing", 300);
	set("inquiry", 
                ([
                       "ι��" : (: ask_job :),
                        "����" : (: ask_over :),
                    
                ]));
	setup();

}

int ask_job()
{
	object me,shi;

	me=this_player();
	if (!me->query_temp("sljob/qingwu/weizhu"))
	{	
		command("say ����Ե�޹ʲ�Ҫ����Ϸ���\n");
		return 1;
	}

	if (me->query_temp("sljob/weizhu/askqiao"))
	{	
		command("say �㲻���Ѿ�������ʳȥι����ô��\n");
		return 1;
	}
	if (me->is_busy()||me->is_fighting()||me->query_condition("job_busy"))
	{
		command("say ����������æ���У�����������\n");
		return 1;
	}
	if (objectp(shi=present("zhu shi",me)))
	{
		command("say ���Ѿ�������ʳ������ȥι��\n");
		return 1;
	}
	message_vision("$N��$n˵������Ȼ�����ޱ����������ģ����ȥ����ι����\n�������Ǽ�������ͷ�Ӳ�֪�����Ķ�ȥ�ˣ������岻�ã�����Ҫ�����ˣ�\n",this_object(),me);
	shi=new("d/shaolin/npc/obj/zhushi");
	shi->move(me);
	me->set_temp("sljob/weizhu/askqiao",1);
	command("say ���������̫������Ҳ��֪�����Ǽҷ��������ô�����������˾��ģ�\n");
//	command("say �����������ˣ��ȷ�������Ϳ���ɱ�˳��ˣ�\n");
	return 1;
}
int ask_over()
{
	object me,shi;

	me=this_player();
	if (!me->query_temp("sljob/weizhu/over"))
	{
		command("say ���ֿ�ʼ͵����Ϊɶ��������ι�ꣿ\n");
		return 1;
	}
	if (objectp(shi=present("zhu shi",me)))
	{
		command("say ���Ѿ�������ʳ������ȥι��\n");
		return 1;
	}
    message_vision("$N��$n˵�������Ѿ�ι���ˣ������鷳���ˣ����ȥ������޴�ʦ��ʾ��л��\n",this_object(),me);
	


	me->delete_temp("sljob/weizhu");
//	command("say ���������̫������Ҳ��֪�����Ǽҷ��������ô�����������˾��ģ�\n");
	command("say �����������ˣ��ȷ�������Ϳ���ɱ�˳��ˣ�\n");
	//�жϿ����Ƽ���ȥ

	me->set_temp("sljob/qingwu/weizhuok",1);

	return 1;
}

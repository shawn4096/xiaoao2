// guanbing.h
// all include �ٱ����佫 by Lklv 2002.1.18
// update by lsxk@hsbbs �����Զ�������grin

#include <get_place.h>
#include <ansi.h>

void init()
{
	object ob;
	int level;
	string *pinji = ({ "�ڴ�", "�����ᶽ","��ͳ","����ͳ","����","�ν�","Ѳ��ͳ��","�λ�", "�߶�˾", "�ر�", "��Ʒǧ��","����","Ѳ��ͷ","Ѳ��" });
	::init();
	if (interactive(ob = this_player())
	 && living(this_object())
	 && ob->query_condition("killer")) {
		remove_call_out("kill_ob");
		call_out("kill_ob", 0, ob);
        }
		else if (ob->query("job_time/�ٸ�")>=10) {
			
			level=13;						
		if (ob->query("job_time/�ٸ�")>=10) level=12;
		if (ob->query("job_time/�ٸ�")>=100) level=11;
		if (ob->query("job_time/�ٸ�")>=500) level=10;
		if (ob->query("job_time/�ٸ�")>=1000) level=9;
		if (ob->query("job_time/�ٸ�")>=5000) level=8;
		if (ob->query("job_time/�ٸ�")>=10000) level=7;
		if (ob->query("job_time/�ٸ�")>=20000) level=6;
		if (ob->query("job_time/�ٸ�")>=40000) level=5;
		if (ob->query("job_time/�ٸ�")>=80000) level=4;
		if (ob->query("job_time/�ٸ�")>=100000) level=3;
		if (ob->query("job_time/�ٸ�")>=200000) level=2;
		if (ob->query("job_time/�ٸ�")>=400000) level=1;
		if (ob->query("job_time/�ٸ�")>=1000000) level=0;
		
			
        message_vision(HIY"�ٱ�����˵������"+pinji[level]+" "+ob->query("name")+"�����ڴˣ������˵��ྲ!��\n"NOR, ob); 
		}
}

int accept_fight(object me)
{
    string p;
    object env = environment(this_object());

    p = get_place(file_name(env));
	if (!me) return 0;
    if(me->query("guanbing_chat_alarm"))
    message("system",HIY"��"+HIR+"�ٸ���Ѷ"+HIY+"��"+this_object()->query("name")+"("+this_object()->query("id")+")����λע�⣡"+HIC+p+HIG+env->query("short")+HIY+"���⵽�������븽��ƽ��Ѹ�ٳ���Σ�յ�����\n"NOR,users());

	if (query("id")=="wu jiang"){
		command("pei ");
		command("say �ҶԳ�͢�������񣬽����ô�ү�ҽ�ѵ��ѵ�㣡\n");
		fight_ob(me);
		return 1;
	}
	command("say ��ү����������ɱ�ţ��������㵹ù��\n");
	if (!is_killing(me->query("id")))
		me->add_condition("killer", 5);
	kill_ob(me);
	return 1;
}

void kill_ob(object ob)
{
    string p;
    object env = environment(this_object());

    p = get_place(file_name(env));
	if (!ob) return;

    if(ob->query("guanbing_chat_alarm"))
    message("system",HIY"��"+HIR+"�ٸ���Ѷ"+HIY+"��"+this_object()->query("name")+"("+this_object()->query("id")+")����λע�⣡"+HIC+p+HIG+env->query("short")+HIY+"���⵽�������븽��ƽ��Ѹ�ٳ���Σ�յ�����\n"NOR,users());

	if (query("id") == "wu jiang")
		command("say �㣡�㣡�㣡���˰������������������������");
	else
		command("say �����������ߣ�����");
	::kill_ob(ob);
}

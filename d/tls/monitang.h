//cre by sohu@xojh 2014
//monitang.h ���浶 vs ������

#include <ansi.h>



int do_baijian(string arg)
{
	object me = this_player();
   
	if( !me->query_temp("hydjj/receive"))
		return notify_fail("������������Ĳ���ã���Ҫ��ʲô��\n");
    if (!arg)
		return notify_fail("��Ҫ��ʲô��\n");
	if (arg=="���ٳ���"||arg=="���ٴ�ʦ"||arg=="������ʦ")
	{
		tell_object(me,HIC"\n\n������˵�����������������Ħ�����µ��ӡ�"+me->query("name")+"ǰ���ݼ����ٴ�ʦ��\n"NOR);
		tell_object(me,HIY"\n\n���ٴ�ʦ˵���������ǰ�����Ҳ�����ˣ��������кι�ɣ���\n"NOR);
	    call_out("bai_1",random(5),me);
	}
	return 1;
}

int bai_1(object me)
{
	
	message_vision(HIR"\n\n$N�����ĵ����������񽣾���ֻͽ������������ʵ�ã������ֺα�������ӣ����������������������\n"
				+"�ĺ��������˴��������ެ���İ����������ɫ΢�䣬ɭ���ʵ�����$N֮�ԣ��ǲ���˵���������������ʽ���������\n"
				+"��ެ������Ҫ�����������������һ����ǲ�ر���פ�������߽����Է���ެ�����֣���$N���˵������ȫ���ע��������\n"
				+"$N����������ެ������Ľ������������飬���������������Դ���֮�ֻ��Сɮ����˾��Ʊض�����������Υ�ҷ�\n"
				+"�ȱ�������������һֱ����Ȱֹ����\n"NOR,me);
	message_vision(HIY"\n\n���ٴ�ʦ������$N�ȼ�Ҫ�˾������ĵ��ֺθ���ϧ��$NԸ����������ʮ���ž������������²��Ұ��졣$N���Ѿ�ͨ\n"
				+"���־��������־��ô�ѩɽ�������书�������������޵��֡���$N˫�ֺ�ʲ����������ʦ֮�⣬��ҪСɮ�����׳�\n"
				+"�����ٴ�ʦ������$N�Ե������µ������񽣾�ͽ������������ʵ�á����Ǳ��������񽣣����$N���ָ��С�����ȷ��$N��˵��\n"
				+"��·����ͽ������������ʵ�ã����ֺ������$N���ܽ�����ȡȥ���ˡ���\n"NOR,me);
	message_vision(CYN"\n\n\n\n���ٴ�ʦ˵������Ȼ��ʦ���˵���Ǿ�"HIR"������(doujian)��"CYN"����Ӯ�����ֶ�$Nʾ�⣬��ʦ�룡\n\n\n\n"NOR,me);
	me->delete_temp("hydjj/receive");
	me->set_temp("hydjj/baijian",1);
	add_action("do_bijian","doujian");
	return 1;
}

int do_bijian()
{
	object me,kurong,bencan,benguan,benxiang,benchen,benyin;
	me=this_player();
	//������һ�����
    me->delete_temp("hydjj/receive");
	
    if (!me->query_temp("hydjj/baijian"))
    {
		return notify_fail("��Ҫ�Լ�������\n");
    }
	if (me->query_skill_mapped("strike")!="huoyan-dao"
		||me->query_skill_prepared("strike")!="huoyan-dao"
		||me->query_skill_mapped("parry")!="huoyan-dao")
    {
		message_vision("�㼤�����似���ǻ��浶��\n",me);
		return 1;
    }
	
	if (time()-me->query("quest/dls/hyd/time")<86400)
    {
		message_vision("�㷽�Ų��Ƕ�����ô������һ�β��۰���\n",me);
		return 1;
		
    }
	if (!objectp(bencan=present("bencan dashi",environment(me))))
	{
		bencan=new("d/tls/npc/ben-can");
		bencan->move(environment(me));		
	}
	
	if (!objectp(benguan=present("benguan dashi",environment(me))))
	{
		benguan=new("d/tls/npc/ben-guan");
		benguan->move(environment(me));
	}
	if (!objectp(benyin=present("benyin dashi",environment(me))))
	{
		benyin=new("d/tls/npc/ben-yin");
		benyin->move(environment(me));
	}
	if (!objectp(benxiang=present("benxiang dashi",environment(me))))
	{
		benxiang=new("d/tls/npc/ben-xiang");
		benxiang->move(environment(me));
	}
	if (!objectp(kurong=present("kurong zhanglao",environment(me))))
	{
		kurong=new("d/tls/npc/kurong");
		kurong->move(environment(me));
	}
	if (!objectp(benchen=present("duan zhengming",environment(me))))
	{
		benchen=new("d/dali/dlhg/npc/duanzm");
		benchen->move(environment(me));
	}
	if (me->query("combat_exp")>15000000)
	{
		
		call_out("super_ben",1,me,bencan);
		call_out("super_ben",1,me,benguan);
		call_out("super_ben",1,me,benxiang);
		call_out("super_ben",1,me,benyin);
		call_out("super_ben",1,me,benchen);
		call_out("super_ben",1,me,kurong);
	}
	

    bencan->fight_ob(me);
	me->fight_ob(bencan);
	benguan->fight_ob(me);
	me->fight_ob(benguan);
	benxiang->fight_ob(me);
	me->fight_ob(benxiang);
	benyin->fight_ob(me);
	me->fight_ob(benyin);
	benchen->fight_ob(me);
	
	me->fight_ob(benchen);
	kurong->kill_ob(me);
	me->kill_ob(kurong);
    me->delete_temp("hydjj/baijian");
    
	me->set_temp("hydjj/fighttls",1);
	//�����ʱʱ�����
	me->set("quest/dls/hyd/temptime",time());
	
	call_out("check_hyd",1,me,bencan,benguan,benxiang,benyin,benchen,kurong);
	return 1;

}
int check_hyd(object me,object bencan,object benguan,object benxiang,object benyin,object benchen,object kurong)
{
	
	//�趨��ʱʱ�䣬60����ɱ�������٣���������������
	int t;
	object book,ztzhu;
	t=time()-me->query("quest/dls/hyd/temptime");

	if (!living(me)||!me
		||!me->query_temp("hydjj/fighttls")
		||(t>60 && objectp(kurong))
		||me->query("qi")<me->query("max_qi")/3)
	{
		message_vision(HIG"\n\n$N��Ȼ��о������������ƣ�����ɮ�㶼������֮�࣬���ж�ʱ����\n"NOR,me);
		message_vision(HIY"\n\n����ٴ�ʦ�ۼ��ֵ���������Ȼ��������������֮���������񽣽����������յ���\n"NOR,me);
		message_vision(HIC"\n\n$N���ɵ����д�ŭ����ȴ�޿��κΡ�\n"NOR,me);
		tell_object(me,HIW"\n\n���ܻ��浶�����ݺ�ս��ʧ�ܣ�\n"NOR);
		me->add("quest/dls/hyd/fail",1);
		me->set("quest/dls/hyd/time",time());
		//logfile
		message("channel:chat", HIC"�����졿���ٳ��ϣ�"+me->query("name")+HIC"�ô�ĵ��ӣ���Ȼ�ҵ�����������Ұ��\n"NOR, users());
		message("channel:chat", HIC"�����졿���ٳ��ϣ������´��������Ħ�Ǻô����ͷ�����µ���Ҳ������˶��ѣ�\n"NOR, users());
		message("channel:rumor", HIM"��ҥ�ԡ�ĳ�ˣ�"+me->query("name")+HIM"��ͼ��������������֮����������ʧ�ܣ�\n"NOR, users());

		if (objectp(ztzhu=present("zitan nianzhu",environment(me)))){
			destruct(ztzhu);			
		}
		return 1;


	}
	if ( !objectp(kurong)||!living(kurong)|| (t<60 && kurong->query("qi")< kurong->query("max_qi")/2))
	{
		message_vision(HIG"\n\n$Nս���������ɣ��۽�������ٴ�ʦ͵͵�شӻ����ͳ�һ�����飡\n"NOR,me);
		message_vision(HIY"\n\n$N���л�Ȼ����֪���Ǿ��Ǵ�˵�������񽣽��ף����ٴ�ʦ��ͼ�������˽����ջ٣�\n"NOR,me);
		message_vision(HIC"\n\n$N�ۼ��ֿ죬ս��֮�࣬���ƻ��浶һ���ֵ�����ն����ٴ�ʦ������\n"NOR,me);
		message_vision(HIR"\n\n���ٴ�ʦ�ҽ�һ����������ͼ�׵����ڵأ�\n"NOR,me);
        
		message("channel:rumor", HIM"��ҥ�ԡ�ĳ�ˣ�"+me->query("name")+HIM"�ɹ���������������֮���������ף�\n"NOR, users());
		
		
		book=new("/d/tls/npc/obj/jianpu");
		book->set("owner",me->query("id"));
		book->move(environment(me));
		//message_vision(HIR"\n\n���ٴ�ʦ�ҽ�һ����������ͼ�׵����ڵأ�\n"NOR,me);
		//���佣��
		if (living(bencan))
		{
			bencan->kill_ob(me);
			me->kill_ob(bencan);
		}
		if (living(benguan))
		{
			benguan->kill_ob(me);
			me->kill_ob(benguan);
		}
		if (living(benyin))
		{
			benyin->kill_ob(me);
			me->kill_ob(bencan);
		}
		if (living(benxiang))
		{
			benxiang->kill_ob(me);
			me->kill_ob(benxiang);
		}
		if (living(benchen))
		{
			benchen->kill_ob(me);
			me->kill_ob(benchen);
		}
		if (living(kurong))
		{
			kurong->kill_ob(me);
			me->kill_ob(kurong);
		}
		me->set_temp("hydjj/tlsover",1);
		me->delete_temp("hydjj/fighttls");
		
		if (objectp(ztzhu=present("zitan nianzhu",environment(me)))){
			destruct(ztzhu);			
		}
		return 1;
	}
	call_out("check_hyd",1,me,bencan,benguan,benxiang,benyin,benchen,kurong);
	return 1;

}
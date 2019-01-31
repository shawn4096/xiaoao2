//cre by sohu@xojh,2014
// monitang.c ���� vs ���浶

#include <ansi.h>
#include "monitang.h"
inherit ROOM;
int do_fight1();
int do_jiejiu(string arg);
int do_baijian(string arg);
int do_bijian();
int check_hyd(object me,object bencan,object benguan,object benxiang,object benyin,object benchen,object kurong);

void create()
{
        set("short", HIY"Ĳ����"NOR);
        set("long",@LONG
���������¸�ɮ�ǵľ���֮����ȫ����ľ���ƣ�����ľ����ľ�Ͼ���ȥ
Ƥ����Ȼ���ӣ���һ·������̻Ի͵ĵ��ý�Ȼ��ͬ�����������Ϸ�������
�������ü���Ϻ��С�
LONG
        );
		set("busy",1);
        set("exits", ([
		"out": __DIR__"lang2",
	]));
	set("objects",([
		__DIR__"npc/ben-guan" : 1,
		__DIR__"npc/ben-xiang" : 1,
		__DIR__"npc/ben-can" : 1,
		//__DIR__"npc/obj/ztnianzhu" : 1,
        ]));
        setup();
}
//���� �����ۡ���������Ĳ����������١�
//���� shaoze�����۶��Ħ�ǣ��ٳ彣��
//���� shangyang,���� �س彣

void init()
{
	   //�ӿڣ�Դ�Կ��ٴ�ʦ��ask kurong about ���Ρ�������ȷ��ֻ��һ��������
		object me,kurong,bencan,benguan,benxiang,benchen,benyin;
		object ztzhu;
		me=this_player();
		ztzhu=new("d/tls/npc/obj/ztnianzhu");
//ע��Ҫ������ʼ����
			
		if (present("zitan nianzhu",environment(me))&&(me->query_temp("tls/fight1")||me->query_temp("hydjj/receive")))
		{
				message_vision(HIC"�����������ڽ��ܣ�����������\n"NOR,me);
				
				return;
		}			
	
        //���������ӿ�    
		if (!present("zitan nianzhu",environment(me))&&me->query_temp("tls/fight1"))
		{
			me->delete_temp("tls/fight1");
			call_out("do_1",1,me);
			
			ztzhu->move(environment(me));
			me->start_busy(999);
			return;
			//me->delete_temp("tls/fight1");
		}
		//���ܻ��浶�ӿ�
		if (!present("zitan nianzhu",environment(me))&&me->query_temp("hydjj/receive"))
		{
			
			add_action("do_baijian","baijian");
			
			ztzhu->move(environment(me));
			
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
			//me->start_busy(2);
			return;


		}
		
}

int do_1(object me)
{
    message_vision(HIC"���ڴ�ʱ��$N�Ƕ˺�Ȼ�ŵ�һ����͵�̴�㣬����һ���������޵���ԶԶƮ����\n"NOR,me);
    call_out("do_2",random(3),me);
	return 1;

}
int do_2(object me)
{
	message_vision(HIC"\n\n\n���ٴ�ʦ˵���������գ����գ����������ݵ����Ҳ����߶�������������Ĳ���������ɡ�����\n"NOR,me);
    call_out("do_3",random(4),me);
	return 1;

}
int do_3(object me)
{
	message_vision(YEL"\n\n\n���ٴ�ʦ������$N������������ǰ���Ǵ���������������Ҳ����������һҪ��ë����\n������������������ģ������������а��⡣\n"NOR,me);
    call_out("do_4",random(4),me);
	return 1;

}

int do_4(object me)
{
	message_vision(HIY"\n\n\n�ſ������һ��ɮ�ˣ�����ɫɮ�ۡ�������ʮ����ͣ�����âЬ��������ɷ���������б���������\n"+
				"���������鱦����Ȼ���ԡ���������ֻ�Ƶü��ۣ������������׽�֮�⡣�ٴӰ���������ȥ��ֻ������վ\n"+
				"�Ű˾Ÿ����ӣ���ò��������η������������ʿ�����Ǵ�����������ެ������������ˡ�\n"NOR,me);
	call_out("do_5",random(4),me);
	return 1;
}
int do_5(object me)
{
	tell_object(me,HIC"\n\n\n���˺�һ�ᣬֻ���ñ����ɵ������������ݣ��������Ĳ���á�����һ���������������ͷ�����·����������\n"
				+"��������������ǫ�ͣ�������񣬾���ǿ�װԺ�֮�ˡ����Ų�������ʮ�����ˡ����ñ����ƿ����ţ�˵�����������룡��\n"
				+"��������������������ٲ��������У�����ٴ�ʦ��ʲΪ��˵��������ެ�����Ħ�ǣ��μ�ǰ����ʦ���г�\n"
				+"�޳���˫�����٣��ϱ��������Ǽٷǿգ������ٴ�ʦȴ����һ����������������ѧ�����Ȼ�����鴫����һ����\n"+
				"�������������ο���������������������Ĳ�ᵱ���ھ�ʬ�ǳ����˫��֮�����𣬶����ϱ�������˫����ÿһ���\n"
				HIG+"\n\n\n����������һ��һ�ݣ���֮Ϊ���Ŀ����١����ݷ����Ե�������˫����Ϊ�������޳������Ϸ�˫����Ϊ���������֡���\n"
				+"����˫����Ϊ���������ҡ�������˫����Ϊ�������޾�����ïʢ�ٻ�֮����ʾ���㱾�ࣺ�����֡��ҡ�������ή���֮��\n"
				+"��ʾ���ࣺ�޳������֡����ҡ��޾�������������˾���֮��������Ϊ�ǿݷ��٣��Ǽٷǿա����ٴ�ʦ��ʮ�꾲��\n"
				+"��������ֻ���޵���ݰ��ٵľ��磬�޷��޵�����һ��ġ��ǿݷ��١�������١�֮��������һ�������������Ļ����㼴\n"
				+"��Ȼ��˵����������Զ��������δ��Զӭ�������ȱ�����\n"NOR);
	call_out("do_6",random(4),me);
	return 1;
}
int do_6(object me)
{
	message_vision(MAG"\n\n\n�Ħ�ǵ�����Сɮ����ʶǳ������δ����ȡ������λ��ʦ��������ʮ�������е�����ָ��������������λ֮ǰ�׳󡣡�\n"+
				"˵��վ��������˵������Сɮ���겻������֮�������������ԣ���ϰ���Ǵ��裬������λָ�㡣��һ·ָ�����黨ָ����\n"+
				"ֻ��������Ĵָ��ʳָ�����ס��������ס��һ���ʻ�һ�㣬��¶΢Ц��������ָ�����ᵯ��\n"NOR,me);
	message_vision(HIC"\n\n\n�����Ħ�ǵ�ָ֮��ȴ�����þߺ���ͨ����������ʮ�º󣬾����������䣬�ſ�������һ������ʱ��������Ʈ��\n"
				+"һƬƬ���Ӵ��Բ����������¶����ʮ���ƿס�ԭ��������ʮ���黨ָ������յ����Լ�����֮�ϣ��������£�\n"
				+"�����������һ���紵��������¶�˳����������뱾�ۡ����ࡢ���Ρ������۵Ȼ������˼��ۣ����ǰ������죺\n"
				+"��ƾ���ǵĹ�������һ��ָ��㣬���´��ף�ԭ�಻�ѣ�����ָ�������������΢Ц�������ˣ�ȴ���������ܡ�\n"
				+"���黨ָ��һ��ָȫȻ��ͬ��  ������������ȷ���������Խ辵֮������\n"NOR,me);
	call_out("do_7",random(4),me);
	return 1;
}
int do_7(object me)
{
	message_vision(HIG"\n\n\n�Ħ�ǵ�����Сɮ����ʶǳ������δ����ȡ������λ��ʦ��������ʮ�������е�����ָ��������������λ֮ǰ�׳󡣡�\n"+
				"˵��վ��������˵������Сɮ���겻������֮�������������ԣ���ϰ���Ǵ��裬������λָ�㡣��һ·ָ�����黨ָ����\n"+
				"ֻ��������Ĵָ��ʳָ�����ס��������ס��һ���ʻ�һ�㣬��¶΢Ц��������ָ�����ᵯ��\n"NOR,me);
	message_vision(HIC"\n\n\n�����Ħ�ǵ�ָ֮��ȴ�����þߺ���ͨ����������ʮ�º󣬾����������䣬�ſ�������һ������ʱ��������Ʈ��\n"
				+"һƬƬ���Ӵ��Բ����������¶����ʮ���ƿס�ԭ��������ʮ���黨ָ������յ����Լ�����֮�ϣ��������£�\n"
				+"�����������һ���紵��������¶�˳����������뱾�ۡ����ࡢ���Ρ������۵Ȼ������˼��ۣ����ǰ������죺\n"
				+"��ƾ���ǵĹ�������һ��ָ��㣬���´��ף�ԭ�಻�ѣ�����ָ�������������΢Ц�������ˣ�ȴ���������ܡ�\n"
				+"���黨ָ��һ��ָȫȻ��ͬ��  ������������ȷ���������Խ辵֮������\n"NOR,me);
	call_out("do_8",random(6),me);
	return 1;
}
int do_8(object me)
{
	tell_object(me,MAG"\n\n�Ħ��΢Ц�������׳��ˡ�Сɮ���黨ָָ�������������µ����ɴ�ʦԶ�ˡ��ǡ�����Ҷָ����ֻ������������\n"
				+"������ת�������ŵ���ľ��첽���У�ʮָ�������㣬����ľ����ľм�׷ɣ���ס��������̼�һֻľ���ѳ�ΪһƬ\n"
				+"Ƭ��Ƭ�������۵ȼ���ָ��ľ�䣬���಻�棬����ľ��Ľ�����ͭƬ�����ۡ���ť�Ƚ���������������ָ���·׷����ѣ�\n"
				+"��Ų��ɵ��ľ���\n"NOR);
	tell_object(me,HIG"\n\n�Ħ��Ц������Сɮʹ�����Ҷָ��һζ�Ե�������ǳª�ý�����˵�Ž�˫��£������֮�У�ͻ��֮�䣬��һ����\n"
				+"ľƬ��Ȼ������Ծ����������������һҪ���ε�ϸ������סȥ��������һ�㡣���Ħ��ʱ��������ʼ�մ����º�Ц\n"
				+"�ݣ�ɮ�����°���Ҳ��Ʈ����֣�ԭ����ָ���������а���������ȫ���μ��������̲�ס�ѿ��޵����������ָ��\n"
				+"�����鴫���������������Ħ�ǹ����������ʦ�佱�ˡ�ľƬԾ�����������ࡣ����Ҫ������ʵ�������������࣬\n"
				+"�������֮����Ҳ�����гɡ��������ʦ������Ľ��������������֮�У������ƽ⡮�����ָ���ķ��ţ����Ħ�ǵ���\n"
				+"���еġ��ƽ�֮������Ӵ�ʦ�ķ��������롣������������Σ�˵�������ţ��Ա��������࣬����֮������\n"NOR);
	tell_object(me,HIR"\n\n�Ħ��ȴ��վ�𣬻����ĵ����������񽣾���ֻͽ������������ʵ�ã������ֺα�������ӣ����������������������\n"
				+"�ĺ��������˴��������ެ���İ����������ɫ΢�䣬ɭ���ʵ���������֮�ԣ��ǲ���˵���������������ʽ���������\n"
				+"��ެ������Ҫ�����������������һ����ǲ�ر���פ�������߽����Է���ެ�����֣����Ħ�����˵������ȫ���ע��������\n"
				+"�Ħ�ǵ���������ެ������Ľ������������飬���������������Դ���֮�ֻ��Сɮ����˾��Ʊض�����������Υ�ҷ�\n"
				+"�ȱ�������������һֱ����Ȱֹ����\n"NOR);
	tell_object(me,HIY"\n\n���ٴ�ʦ�����������ȼ�Ҫ�˾������ĵ��ֺθ���ϧ������Ը����������ʮ���ž������������²��Ұ��졣�������Ѿ�ͨ\n"
				+"������ʮ�����������־��ô�ѩɽ�������书�������������޵��֡����Ħ��˫�ֺ�ʲ����������ʦ֮�⣬��ҪСɮ�����׳�\n"
				+"�����ٴ�ʦ�����������Ե������µ������񽣾�ͽ������������ʵ�á����Ǳ��������񽣣�����������ָ��С�����ȷ��������ȥ��\n"
				+"��·����ͽ������������ʵ�ã����ֺ�������������ܽ�����ȡȥ���ˡ���\n"NOR);
	call_out("do_start",random(6),me);

	return 1;
}

//��ʼս�����ڡ���

int do_start(object me)
{
    
	tell_object(me,CYN"\n\n�Ħ��˫��һ���������߽�һ���ߴ��ӡ��Ħ��˵�˼��䷬�����Ǻ��ӵ�ͷ��Ӧ���������������ȡ��һ�����㣬���˸��Ħ�ǣ�\n"
				+"�����ų��š����˶�����֣�����������һ�����ϣ��ѵ������������У�ֻ������������һ֦���㣬����ȡ�����µ�һЩľм��\n"
				+"������������������ľм֮�С����һ��������֦���㣬����һ�У�ÿ֦��������Լһ�ߡ��Ħ����ϥ������󣬸���������ң�\n"
				+"ͻ��˫�ƴ���˼��꣬����ӳ���������ͷһ����ͬʱ��ȼ�ˡ����˶��Ǵ��һ����ֻ�������֮ǿ��ʵ�ѵ��˲���˼��ľ��硣\n"
				+"�������漴�ŵ�΢΢������֮�����µ�����֦����ͷ�϶��л�ҩ���Ħ�ǲ������������㣬����������ĥ����ҩ��ʹ֮������ͷ��\n"
				+"������Ȼ�������ܣ��������۵���������Ҳ�ɰ쵽��\n"NOR);
        call_out("do_start1",4,me);
		return 1;

}
int do_start1(object me)
{
        tell_object(me,HIG"\n\n\n\n������������������֮ɫ��������ֱ���������������Ħ��˫���籧Բ�������˳��������������������������ֱ�ָ��\n"
				+"���١����ۡ����ࡢ���򡢱��Ρ����������ˡ��������������������浶��������������翣�����׽����ȴ��ɱ�����޺���ʵ��\n"
				+"�����������˷���ֻ־�ڵþ����������ˣ����Ե�����֦���㣬��չʾ�ƹ�����ȥ���μ���һ���Ե������޿֣�������ʾ�ȱ�\n"
				+"Ϊ����ֻ�ǽ�����ѧ��Ϊ������ɱ��������\n"NOR);
		call_out("do_start2",4,me);
		return 1;

}
int do_start2(object me)
{
	tell_object(me,MAG"\n\n\n\n�������������������ǰ����֮�����㼴ͣס����������ȶ�����һ�����������������ͱ��̲�ɰΪ�ѣ�������Ʈ���޶���\n"
				+"�������ڰ�գ��ǿ�����ʮ���ˡ���������Сָһ�죬һ���������ٳ�Ѩ�м����߶�����ָ����ǰ�ı��̡������������������һ�ƣ�\n"
				+"Ѹ���ޱȵ����Ħ�ǵ����߹�ȥ����������ǰ����ʱ���Ħ�ǵġ����浶��������ʢ�������޷�����ǰ�С��Ħ�ǵ��˵�ͷ������\n"
				+"�������鴫���������й�Ȼ�С����󽣡�һ·�����������˵������������У����δ�ʦ֪���������������������Է��ӽ����е�������\n"
				+"����վ������������б������������Сָ�������������ҵ�б����ȥ���Ħ������һ������ʱ��ס��\n"NOR);
    call_out("do_fight1",3,me);
    return 1;
}

int do_fight1()
{
	object me=this_player();
	object bencan,benguan,benxiang,benyin,kurong,benchen,jiumozhi;

	if (!objectp(bencan=present("bencan dashi",environment(me))))
	{
		bencan=new("d/tls/npc/ben-can");
		bencan->move(environment(me));
	}
	if (!objectp(jiumozhi=present("jiumo zhi",environment(me))))
	{
		jiumozhi=new("kungfu/class/xueshan/jiumozhi");
		jiumozhi->move(environment(me));
		
	}
	    jiumozhi->add_temp("apply/armor",300);
		jiumozhi->add_temp("apply/parry",300);
		jiumozhi->add_temp("apply/defense",1000);
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
	if (!objectp(kurong=present("kurong u",environment(me))))
	{
		kurong=new("d/tls/npc/kurong");
		kurong->move(environment(me));
	}
	if (!objectp(benchen=present("duan zhengming",environment(me))))
	{
		benchen=new("d/dali/dlhg/npc/duanzm");
		benchen->move(environment(me));
	}
 
	call_out("do_fight2",5,me,jiumozhi,kurong);
	tell_object(me,HIY"���δ��һ�����������ͽ̣�����һָ������������\n"NOR);
	bencan->fight_ob(jiumozhi);   
	jiumozhi->fight_ob(bencan);
	
	
	tell_object(me,HIC"\n\n\n�����ۼ����˽��������ݺᣬ�Ħ�ǿ����������࣬���Ǻȵ����������ˡ���˵������һָ��һ�ɾ��������\n"NOR);
	tell_object(me,HIR"\n�Ħ�Ǻȵ������ã��ٳ彣������������\n"NOR);
	benguan->fight_ob(jiumozhi);   
	jiumozhi->fight_ob(benguan);
    tell_object(me,HIY"\n\n\n�����ɼ�ʦ��ʦ�����֣�ռ����˿���Ϸ磬�����������⽣��δ�죬���������þ�������Խ�����Խ�ã�\n"
					+"������������������������������ڹ۲챾�ۡ����ζ��˵Ľ�����δ��ȫ������������˵���������ࡢ������λ\n"
					+"ʦ�ܣ����Ƕ��ǳ��ְɡ���ʳָ�촦��������������չ�������ű���ġ��ٳ彣���������۵ġ��س彣������·������\n"
					+"�����������ϻ�ȥ��\n"NOR);
    tell_object(me,HIB"\n\n�����۳�̾һ�������һָ���������죬���ǡ��س彣������ʽ��\n"NOR);
    benchen->fight_ob(jiumozhi);
	jiumozhi->fight_ob(benchen);
	
	tell_object(me,HIR"\n\n�������һָ���������죬���ǡ�������������ʽ��\n"NOR);
	benyin->fight_ob(jiumozhi);
	jiumozhi->fight_ob(benyin);
	tell_object(me,HIG"\n\n�������һָ���������죬���ǡ��ٳ彣������ʽ��\n"NOR);
	benxiang->fight_ob(jiumozhi);
	jiumozhi->fight_ob(benxiang);
	
	tell_object(me,HIW"\n\n\n���ٴ�ʦ�����ָд����������Īʧ������۽����Թ���ѧ����Υ��ѵ����\n\n\n"NOR);
	message_vision(HIR"\n\n\n���ٴ�ʦ����������˫��Ĵָͬʱ����������������죬���Ħ��������硣���������������֣���ǲ��·\n"
						+"��ʧ��Ϯ���������ϵ��Ħ�ǵĻ��浶���������ƻ�������Ҫ�˵��Լ�������Ƭ�̣����������������ɴ�\n"
						+"�����ֲ�����\n"NOR);
	
	return 1;
	
}

int do_fight2 (object me,object jiumozhi,object kurong)
{
	
	tell_object(me,HIW"\n\n\n���ٴ�ʦ�����ָд����������Īʧ������۽����Թ���ѧ����Υ��ѵ����\n\n\n"NOR);
	tell_object(me,HIR"\n\n\n���ٴ�ʦ����������˫��Ĵָͬʱ����������������죬���Ħ��������硣���������������֣���ǲ��·\n"
						+"��ʧ��Ϯ���������ϵ��Ħ�ǵĻ��浶���������ƻ�������Ҫ�˵��Լ�������Ƭ�̣����������������ɴ�\n"
						+"�����ֲ�����\n"NOR);
		
	kurong->fight_ob(jiumozhi);
	jiumozhi->fight_ob(kurong);
	call_out("do_fight3",1,me,jiumozhi,kurong);
    return 1;

}
int do_fight3(object me,object jiumozhi,object kurong)
{
    
	//tell_object(me,HIR""NOR);
    if (kurong->is_fighting(jiumozhi)||jiumozhi->is_fighting())
    {
		call_out("do_fight3",3,me,jiumozhi,kurong);
		return 1;
    }
   
	tell_object(me,HIR"\n\n����������������������������֮�У�ֻ���������ɮ���ڵ��£�����ׯ�ϣ��������뱾�ε���ɫ��\n"
					+"\n���Ǵ��Ա��ߡ��Ħ��һ��֮�£���ʱʡ�򣬰��У������ã���������ɮ֪�����У���Ȼ�������񽣵�ͼ�����ˡ���\n"NOR);
	
	tell_object(me,HIC"��\n\n\n\n\n���ٴ�ʦ��һ��ָ�������Ƶ�����ͼ�׷�����������Ħ����ֹ���ᣬ�����ƶ���������������ʹ������������\n"
					+"��������ɢ����ͼ�����յøɸɾ���������Ⱦ��Ǿ���һ��ָ�ĸ��֣�һ�����̣���֪Ե�ɣ�����ʦ����Ϊ���飬\n"
					+"������ȫ�����Ľ�������֮����ȥ��������֮������֡������������зֱ�ǵ�һ����������ǿ����ȥ������Ĭд\n"
					+"�������ǣ�ֻ�����洫��ͼ��ȴ���ھʹ˻��ˡ�\n"NOR);
	
	tell_object(me,HIG"\n\n\n�Ħ���־���ŭ���������Ǽ��Ը�������ȴ�������ΰ��ڿ��ٴ�ʦ�����£������񽣺���ѻ�ȥ�������ͽ\n"
						+"Ȼ���¸�ǿ��ȴ�Ǻ����ջ���վ����������ʲ˵���������ٴ�ʦ�αظ����˶������۲������ļ����¡�\n"
						+"���±�����Сɮ���٣����´��ǹ��ⲻȥ�����ڴ˾���һ��֮���������ã����벻�٣�ԭ�޶��ֱ���͸�ǡ���\n"
						+"��΢һת���������ٺͱ���Դ�ͻȻ�����ֿ�ס�˱���������������˵�������ֹ��������������۷緶������\n"
						+"һ�����������ϻ������ݣ�����ެ��һ�𡣡�\n"NOR);
	//call_out("do_help",2,me,jiumozhi);
	//����Ħ�Ǵ������ܽ��,��10���ӽ�Ȳ��ˣ����Ħ������
   // call_out("do_escape",20,me,jiumozhi);
	if (objectp(jiumozhi=present("jiumo zhi",environment(me))))
	{
		
		tell_object(me,HIC"��ʼ����ˡ�test��\n"NOR);     
	    add_action("do_jiejiu","jiejiu");
		me->start_busy(-1);
		me->set_temp("liumai/jiejiu",time());
	}
	return 1;
    
}

int do_jiejiu(string arg)
{
	object me=this_player();
	object jiumozhi;
    


	if (!arg || arg!="������")
	{
		message_vision("��Ҫ���\n",me);
		return 1;
	}
	if (time()-me->query("quest/tls/liumai_1/time")<86400)
    {
		message_vision("�㷽�Ų��Ǹս�ȹ�һ��ô������һ�β��۰���\n",me);
		return 1;
		
    }

	message_vision(HIY"$N�ۼ������۱���ެɮ���ƣ����д󼱣����һ��������ȥ�����Ħ�Ǵ���һ����ͼ��ȱ����۳�����\n"NOR,me);
	if (!objectp(jiumozhi=present("jiumo zhi",environment(me))))
	{
		jiumozhi=new("kungfu/class/xueshan/jiumozhi");
		jiumozhi->move(environment(me));		
	}
	jiumozhi->add_temp("apply/armor",300);
	jiumozhi->add_temp("apply/parry",300);
	jiumozhi->add_temp("apply/defense",1000);
	me->kill_ob(jiumozhi);
	jiumozhi->kill_ob(me);
	call_out("do_check",3,me,jiumozhi);
	
	return 1;

}


int do_check(object me,object jiumozhi)
{
    object kurong,benchen,benyin; 
	object ztzhu;
	if (!me)
	{
		message("channel:chat", HIC"�����졿�Ħ�ǣ�"+me->query("name")+"ʢ��֮�£���ʵ�ѷ���������ˣ��ߣ�\n"NOR, users());
		message("channel:chat", HIC"�����졿�Ħ�ǣ������ºô����ͷ��Ҳ������˶��ѣ��ߣ�\n"NOR, users());
		message_vision(HIY"ս������������ʧ�ܡ�\n"NOR,me);
		call_out("do_leave",2,me);
		return 1;

	}
	if (time()-me->query_temp("liumai/jiejiu")>20)
	{
		message_vision(HIY"�Ħ����Ȼһ����������ľ�����ץס�����ۣ������ȥ!\n"
						+"\n\nս������������ʧ�ܡ�\n"NOR,me);
	    
		call_out("do_leave",2,me);
        return 1;
	}
	if (!living(jiumozhi)||!objectp(jiumozhi))
    {
		tell_object(me,HIR"�Ħ������������˵���������²����Ի�����Ȼ�и��ִ��ڣ��ߣ��Ҵ����¸���û�ꡣ\n"NOR);
		tell_object(me,HIR"�Ħ������������˵�������Ӷ�ʮ�������һ���ú���\n"NOR);

		message("channel:chat", HIC"�����졿���ٴ�ʦ����������������������������˶��ѣ�����������������ǽ����ˣ�\n"NOR, users());
		message("channel:chat", HIC"�����졿���ٴ�ʦ���������������µ�һ���£������񽣱ض����ｭ����\n"NOR, users());
		message("channel:chat", HIC"�����졿���ٴ�ʦ��"+me->query("name")+"�����޲����Ϸ���˳�ۣ�\n"NOR, users());

		tell_object(me,HIY"\n���ٴ�ʦ˫�ֺ�ʮ�����������������ӷ𡱣�Ȼ��ת�����˵��������Υ����ѵ���㵽����Է��һ�Ρ���\n"NOR);
        if (objectp(kurong=present("kurong zhanglao",environment(me))))
	  		kurong->move("d/tls/lsy");
		
		tell_object(me,CYN"\n�����۳�̾һ�������������������ӷ𡱣�\n"NOR);
        if (objectp(benchen=present("duan zhengming",environment(me))))
	  		//benchen->move("d/dali/huanggong");
		destruct(benchen);
		
		tell_object(me,HIC"\n������λ��ʦҲ�Ǹп���ǧ�����ɵ����ſ��ٴ�ʦ����ȥ���Ȼһ̾��\n"NOR,me);
		
		destruct(present("benyin dashi",environment(me)));
		
		me->set_temp("liumai/fightzhiok",1);
		//���ܽ�����ȡ��busy����ֹ���˽��ܵ��µĻ���
		if (objectp(ztzhu=present("zitan nianzhu",environment(me)))){
			destruct(ztzhu);			
		}
        return 1;
    }
	
	if (jiumozhi->query("qi")<jiumozhi->query("max_qi")/2 
		&& jiumozhi->is_fighting(me))
    {
		tell_object(me,HIR"�Ħ�����һ����˵���������²����Ի�����Ȼ�и��ִ��ڣ��ߣ�������ڣ�˵�������Ծȥ��\n"NOR);
		destruct(jiumozhi);
		message("channel:chat", HIC"�����졿�Ħ�ǣ�"+me->query("name")+"����ҵ��ţ��Ҵ����¸���û�꣡\n"NOR, users());
		message("channel:chat", HIC"�����졿���ٴ�ʦ����������������������һ·�ߺã�\n"NOR, users());
		message("channel:chat", HIC"�����졿���ٴ�ʦ���������������µ�һ���£������񽣱ض����ｭ����\n"NOR, users());
		message("channel:chat", HIC"�����졿���ٴ�ʦ��"+me->query("name")+"�����޲����Ϸ���˳�ۣ�\n"NOR, users());

		tell_object(me,HIY"\n���ٴ�ʦ˫�ֺ�ʮ�����������������ӷ𡱣�Ȼ��ת�����˵��������Υ����ѵ���㵽����Է��һ�Ρ���\n"NOR);
        if (objectp(kurong=present("kurong zhanglao",environment(me))))
	  		kurong->move("d/tls/lsy");
		
		tell_object(me,CYN"\n�����۳�̾һ�������������������ӷ𡱣�\n"NOR);
        if (objectp(benchen=present("duan zhengming",environment(me))))
			destruct(benchen);
		
		tell_object(me,HIC"\n������λ��ʦҲ�Ǹп���ǧ�����ɵ����ſ��ٴ�ʦ����ȥ���Ȼһ̾��\n"NOR,me);
		
		destruct(present("benyin dashi",environment(me)));
		//�ɹ����
		me->set_temp("liumai/fightzhiok",1);
		me->set("quest/tls/liumai/winzhi",1);
		//���ܽ�����ȡ��busy����ֹ���˽��ܵ��µĻ���
		if (objectp(ztzhu=present("zitan nianzhu",environment(me)))){
			destruct(ztzhu);			
		}
        return 1;
    }
	
	if (jiumozhi->is_fighting(me))
	{
		remove_call_out("do_check");
		call_out("do_check",1,me,jiumozhi);
		return 1;
	}

}

int do_leave(object me)
{
	object kurong,jiumozhi,benyin,dzm;
	object ztzhu;
	if (objectp(jiumozhi=present("jiumo zhi",environment(me))))
	{
		message("channel:chat", HIC"�����졿�Ħ�ǣ�"+me->query("name")+"ʢ��֮�£���ʵ�ѷ�������һ�߾��ҷ������ߣ�\n"NOR, users());
		message("channel:chat", HIC"�����졿�Ħ�ǣ������ºô����ͷ��Ҳ������˶��ѣ��ߣ�\n"NOR, users());
		destruct(jiumozhi);			
		

	}
	if (objectp(benyin=present("benyin dashi",environment(me))))
	{
		tell_object(this_object(),HIY"�����ʦ�Ȼһ̾�������벻�������¾�Ȼ����������ѣ�����������������\n"NOR);
		destruct(benyin);

	}
	if (objectp(kurong=present("kurong zhanglao",environment(me))))
	{
		tell_object(this_object(),HIY"���ٴ�ʦ�Ȼһ̾�������벻�������¾�Ȼ����������ѣ�\n"NOR);

		destruct(kurong);

	}
	if (objectp(dzm=present("duan zhengming",environment(me))))
	{
		destruct(dzm);

	}
   if (objectp(ztzhu=present("zitan nianzhu",environment(me)))){
			destruct(ztzhu);			
		}
	me->add("quest/tls/liumai_1/fail",1);
    me->set("quest/tls/liumai_1/time",time());

	return 1;

}

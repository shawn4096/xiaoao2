// Modify By River 98/12
inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "��Ժ");
	set("long", @LONG
���˺�ԺС�ᣬ���Ǽ��ª��С���ӣ����Ϸ��ż������ţ����׵�������
����һ���������ƣ����иߴ����ɮ��
LONG
	); 
	set("exits", ([ /* sizeof() == 1 */
	    "south" : __DIR__"dadian",
        ]));

        set("objects", ([
        	__DIR__"npc/huangmei" : 1,
        ]));

	set("coor/x",-200);
  set("coor/y",-400);
   set("coor/z",10);
   setup();
}

void init()
{
     object ye,me,huang,gao,yun,yue,yanqing;
	 me = this_player();
     //һ��ָ�����
	 if(me->query_temp("yyzhi/helpnhs"))
     {
        tell_object(me,HIY"\n\n\n��һ���ţ���Ȼ�����������ڽ���һ�����ҵ�ս����������ӰΧ��һλ��ɮ������ɱ��\n\n"NOR);

		if (!objectp(ye=present("ye erniang",environment(me))))
		{
			ye=new("d/dali/wuliang/npc/erniang");
			ye->move(this_object());
		}
		if (!objectp(huang=present("huangmei heshang",environment(me))))
		{
			huang=new("d/dali/dalieast/npc/huangmei");
			huang->move(this_object());
		}
		/*
		if (!objectp(gao=present("gao shengtai",environment(me))))
		{
			gao=new("d/dali/npc/gaoshengtai");
			gao->move(this_object());
		}*/

		if (!objectp(yun=present("yun zhonghe",environment(me))))
		{
			yun=new("d/dali/wuliang/npc/yunzhonghe");
			yun->move(this_object());
		}
		if (!objectp(yue=present("nanhai eshen",environment(me))))
		{
			yue=new("d/dali/wuliang/npc/eshen");
			yue->move(this_object());
		}
		if (!objectp(yanqing=present("duan yanqing",this_object())))
		  {
			  yanqing=new("d/dali/wuliang/npc/dyq1");
			  yanqing->move(this_object());
		  }
	
		yue->kill_ob(huang);
		//yue->kill_ob(gao);
		yue->kill_ob(me);
		yun->kill_ob(me);
		yun->kill_ob(huang);
		ye->kill_ob(me);
		ye->kill_ob(huang);
		yanqing->kill_bo(me);
		yanqing->kill_bo(huang);
		call_out("check_huang",1,me,huang);
    }
	  //��μҽ��Խ���ָ
	 else if (me->query_temp("yanqing/askzhong"))
	  {
		  if (!objectp(yanqing=present("duan yanqing",this_object())))
		  {
			  yanqing=new("d/dali/wuliang/npc/dyq");
			  yanqing->move(this_object());
		  }
		    if (!objectp(huang=present("huangmei heshang",environment(me))))
		  {
			huang=new("d/dali/dalieast/npc/huangmei");
			huang->move(this_object());
		  } 
		  tell_object(me,HIG"һλ���ۿ������վ���Ƕ����Ը�����˵��������ü�϶������Ȼ�ܶ������Ķ��ݣ��Ͳ�Ҫ��ء�!\n"NOR);
		  tell_object(me,HIG"���������Ϲ���ָ������������ˣ����黨�¾͹����ˣ�����Ӯ�ˣ��Ҿͼ������̡�!\n"NOR);
		  call_out("huang_duan",3+random(2),me,yanqing,huang);/**/

	  }
}

int check_huang(object me,object huang)
{
	
	object ye,yun,yanqing,yue;
	ye=present("ye erniang",this_object());
	yue=present("nanhai eshen",this_object());
	yun=present("yun zhonghe",this_object());
	yanqing=present("duan yanqing",this_object());
	//gao=present("gao shengtai",this_object());
	if (!me)
	{
		return 0;
	}
	if (!objectp(huang)||huang->query("qi")<huang->query("max_qi")/3)
	{
		tell_object(me,HIW"��üɮ�ܵ��Ĵ����Ϯ�����������أ��޷�����������롣\n"NOR);
		tell_object(me,HIW"��Ԯ����ʧ�ܣ���\n"NOR);
		me->add("yyzhi/tls/yyz/start/fail",1);
		me->delete_temp("yyzhi");
		if (objectp(ye)) destruct(ye);
		if (objectp(yue)) destruct(yue);
		if (objectp(yun)) destruct(yun);
		if (objectp(yanqing)) destruct(yanqing);
		
		return 1;

	}
    if (!me->is_fighting()
		&&!objectp(ye)
		&&!objectp(yue)
		&&!objectp(yun)
		&&!objectp(yanqing)
		&&objectp(present("huangmei heshang",this_object())))
	{
		tell_object(me,HIW"���ڽ��Ĵ���˴��ܡ�\n"NOR);
		tell_object(me,HIW"���üɮ��Ԯ����ɹ�����\n"NOR);
		me->delete_temp("yyzhi");
		me->set_temp("yyzhi/helpnhsover",1);
		me->set("yyzhi/tls/yyz/start/helpnhsover",1);
		if (objectp(ye)) destruct(ye);
		if (objectp(yue)) destruct(yue);
		if (objectp(yun)) destruct(yun);
		if (objectp(yanqing)) destruct(yanqing);
	
		return 1;

	}
    call_out("check_huang",1,me,huang);
	return 1;


}

//�⽣��

int huang_duan(object me,object yanqing,object huang)
{

	tell_object(me,HIY"��Ȼ����֮�У��ǾͲ��ò�Ҫ��ԣ�Ϊ������������˰�����ľͲ��ƴ��ˣ�\n"NOR);
	huang->fight_ob(yanqing);
	yanqing->fight_ob(huang);
	

}
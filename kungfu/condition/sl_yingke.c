// sl_yingke.c

#include <ansi.h>
#include <login.h>

int update_condition(object me, int duration)
{
        if (duration < 2) {
			         tell_object(me, HIC "��������΢΢Ц��Ц�����������ͷ˵�����ɵĲ���\n" NOR);

                    tell_object(me, HIY "����ӭ��ͤ��æӭ�ӿ��˵�ʱ���ѵ������ȥ�����޴�ʦ�����ɣ�\n" NOR);
					me->set_temp("sljob/qingwu/yingked",1);
                return 0;
        }
		if (!living(me))
		{
			write(HIR"������������ε��ˣ����г���̾��һ�������������˵�!\n"NOR);
			write("���޷����ϻ����޵��İ�!\n");
			write("����ʧ�ܣ���ȥ�����ޱ���������һ��");
			me->delete_temp("sljob");
			me->clear_condition("sl_yingke");
			return 1;
		}
		switch (random(5))
		{
			case 0:
				message_vision(HIC"$N���г��ҹҵ���ɮ������ѯ��·������æ��ǰ��æָ�㣡\n"NOR,me);
				me->add("jingli",-10);
				me->add_busy();
				break;
			case 1:
				write(MAG"һȺ����·�����㼱æ��æ���Ű��࣬æ����ͷ�󺹣�\n");
				me->add("jingli",-10);
				me->add_busy();
				break;
			case 2:
				write(YEL"�м���������ʿ��ͼ��ս���ָ�ɮ������ָ�ֻ��ţ��㾡��������������Ȱ�⣬��Ϊ�ķ�����\n");
				me->add("jingli",-15);
				me->add("jing",-15);
				me->add_busy();
				break;
			default:
				write(CYN"�������������������Ϊ��ʢ����æ����ͷ�󺹣�\n"NOR);
				break;
		}
        me->apply_condition("sl_yingke", duration - 1);
        return 1;
}

string query_type(object me)
{
	return "job";
}

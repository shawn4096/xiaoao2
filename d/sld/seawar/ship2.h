// 1/28/2002	by augx@sj

void change_short()
{
	if(query("mode")==1) {
		set("short","�����ڴ�");
		set("long",@long
�����Ҿ޴��ս������������������ɲ����������������ս����ս������
�ǰ�����һ�㾫���Ƴɵ����ף����԰���ľ�ļװ����Φ�ˣ�����쳣��һ��
�ڻ�ʹֱ������Ҳ�޷���������ƻ�����Φ�˶�һ�����������һ�������
�������������ݡ���ս����Ϊ�����װ���������ޱȣ������ٶ�����������Ҳ
��Щ������ս��ǰ�װ�������һ����ڣ�������ǿ���ƾ�������
long);
	}
	else {
		set("short","����");
		set("long",@long
���������壬��ʮ���ľ��������ɣ������ʵ���ܹ�����һ��ķ��ˡ�
�����÷�������һ�����Ƿ����ṩ������������Ϊ��С�ɣ��ٶȺܿ죬�Һܲ�
���ױ��ڻ���С�		
long);
	}
}
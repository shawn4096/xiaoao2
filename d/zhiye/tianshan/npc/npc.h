// Npc: /d/tianshan/npc/npc.h
// By Linux
//modified by zhuifeng@SJFY

void attempt_apprentice(object ob)
{

		      
        if( (string)ob->query("gender") == "����" ) {
                command ("say �Բ������չ��似�˵��Ҵ��У���������ƽ�⣬���չ�����");
                return;
        }
        if( !ob->query("quest/tonglao/pass"))  {
			command("��ͱ�����Ե�޹ʣ�ƾʲô���Խ������չ���\n");
            return;
        }
        command("say �ף�ԭ�����㰡��ͯ���Ѿ��Ը��ˣ�����ȥ������������������԰���Ϊʦ��");
        command("xixi "+ob->query("id"));
		//command("recruit " + ob->query("id"));
        
         return;
}


LuaQ                %      A@  @ 
   A�  ��  ��  �  A�  ��  ��  �  A �    �     �   �      �        ��B �B       �  �     �� ��  �� ��  � � �B  � 
      NSExec    luasub nsamake               @      �?   NSCOM_nsamake    creat_index    int2s    int2l    ft        
   P   	  .     A@  @    A�  @ �  A  �       W@A  �   W A @ �@       A� @    A� @    A  @    A@ @    A� @    A� @    A  @    A@ @    A� @ � ��  �   @� � �� D � @   �  � �@ ŀ ���� E�  ��  @ �   �   �@  A� �� �F�A � @   ��  �� � FA �� ��AB �@��@ �� ��G�  �@ �@ ��H�� 	 ���@I@��   �	 �@ ��	 �  � ��   
 �@ �   A
 �@ ˀJE�
 � \� � ��� �@  �@  AA � �� Ɓ�� BKF���� � � K�J� C E ���\� � ����� � ��� \B  �@��    �@ �   A �@ �   � �@ ��  � ܀ � �� ���  A ܀ ̀��  �� ܀� � � �@  AA �@��A Ɓ�� D F��F��BA ܁��J�B�� ��B  ��B   @A���D F��F��B�� �� D� BD NB� ��	�� PD�OB�OB�� �� �F� � �PN�� ��  @ � ��� �B C @ �� ��� �B�� �B � �B��B �B ��RD �� �B�� �BA�  A� �B � � D � ��B� A� �� B�B A� ��� � B�B B� � ���O�@ �� ܀� � � �� � �  EA �� ��D�� ��� \�    � �E  �� �� ��B E� ��\ ܁  � E� F�� � \���B ��\A E  �� \A  � P      NSExec    erasetextwindow 0 :   setwindow 25,25,25,16,25,25,0,2,0,1,1,#ffffff,0,0,800,600    NSGetIntValue               �?   #ffff00    ���nsa ������ߡ��    ������������Ʒ���                    �汾��1.0     br *   #ffffff�뽫��Ҫ������ļ�����input �ļ��� /   ��������뱣�ֻ��������������г�����֧�ֺ�̨��    ���������ʼ�����\     ��ʼ������������    NSTimer    creat_index    ft    math    ceil      @�@   ����������ϣ��ļ�����     ����ʱ    string    format    %02s 	   tostring    ��    %02d    ��    os    execute    mkdir output    io    open    output/arc.nsa    wb  <   ��������ļ�ʧ�ܣ����ֶ�����output�ļ��в��Ҽ��д��Ȩ�ޣ�        �   ����ļ���arc.nsa     д����������    write    int2s    int2l    gsub    name    /    \          offset    size    ����д����ɡ�    ����д������������    getcursorpos %10,%11       $@      l@      &@      ;@   input/    rb    read    *a    close    modf       �@   floor       Y@	   NSSpLoad    :s/24,24,1,1;#ffffff    .      M/s     NSSpVisible 	   NSSpMove      @_@     �o@     	   NSUpdate    �����ɣ�����ʱ��    ��������˳���                     R   s     j      @@ A�  @    �@ A  @ @ �A A�  �� ��A  �@B � ����  � ���  �@���B ����C����� A �� @D����� A� �� @   � �   �@���� A �� @E  ����A ��A�� � K��� C \� �A�� ���W F@	��  � C@� �� ��A� �C ܂ U�� �B � ���BG�� ����  ���  F�B  � E� F��B�\� BBH�  �D �D 	�@  @���H �@  � #      os    remove 
   index.txt    execute    ls -R -F >index.txt    io    open    r    input/    lines        .:    sub       �   :       @      @   input       �?       �       @   d     /    rb     name    string       "@   size    seek    end    offset    len       ,@   close                     v   z        P @ �@  � @�@  ƀ�  ܀ A  �@@� � � ��   �          p@   string    char                     |   �        E   �@@ \� �   ŀ  ���A@ �  ��  �   � � ��   �       int2s       �@   math    floor                     �   �        P @ �@  � @�   � � � �          N@                            
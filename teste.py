import  speech_recognition  as  sr 
import  serial 

arduino  =  serial . Serial ( port = '/dev/ttyUSB1' ,  baudrate = 9600 ,  timeout = 1 ) 

#Function responsible for listening and recognizing speech 
def  listen_microphone (): 
    # Enable the microphone to listen to the user 
    microfone  =  sr . Recognizer () 
    with  sr . Microphone ()  as  source : 
        # Call the noise reduction function available in speech_recognition 
        microfone . adjust_for_ambient_noise ( source ,  duration = 3 ) 
        # Warn the user that you are ready to listen 
        print ( "Say something: " ) 
        # Store the audio information in the variable 
        audio  =  microfone . listen ( source ,  timeout = 2 ,  phrase_time_limit = 3 ) 
    try : 
        #Pass the audio to speech_recognition's pattern recognizer 
        frase  =  microfone . recognize_google ( audio , language = 'pt-BR' ) 
        
        # If it has not recognized the speech pattern, display this message 
    except  sr . UnknownValueError : 
        print ( "I don't understand" ) 

    return  frase 

while  True : 
    input ( 'Enter to continue...' ) 
    sentence  =  listen_microphone () 
    sentence = sentence.lower()
    print ( 'Sentence: '  +  sentence ) 

    if ( 'luiza desativar a iluminação interna'  ==  sentence): 
        
        arduino . write ( bytes ( 'b' ,  encoding = 'utf-8' )) 
        print('iluminação desativada')
        continue 

    if ( 'ativar iluminação interna'  ==  sentence ): 
        arduino . write ( bytes ( 'a' ,  encoding = 'utf-8' )) 
        print('iluminação ativada')
        continue
    
    
    if ( 'hora de curtir'  ==  sentence ): 
        arduino . write ( bytes ( 'c' ,  encoding = 'utf-8' )) 
        print('modo balada on')
        continue
    
    
    if( 'ativar luz externa' == sentence):
        arduino . write ( bytes ( 'f' ,  encoding = 'utf-8' )) 
        print('luz de fora ativada')
        continue
    
    if( 'desativar luz externa' in sentence):
        arduino . write ( bytes ( 'g' ,  encoding = 'utf-8' )) 
        print('luz de fora desativada')
        continue
    
    
    if( 'perigo' == sentence):
        arduino . write ( bytes ( 'h' ,  encoding = 'utf-8' )) 
        print('luzes vermelhas ativadas')
        continue
    
    if( 'tudo calmo' == sentence):
        arduino . write ( bytes ( 'i' ,  encoding = 'utf-8' )) 
        print('luzes vermelhas desativadas')
        continue
    
    if( 'abrir a porta' == sentence):
        arduino . write ( bytes ( 'd' ,  encoding = 'utf-8' )) 
        print('porta aberta')
        continue
    
    if( 'fechar a porta' == sentence):
        arduino . write ( bytes ( 'e' ,  encoding = 'utf-8' )) 
        print('porta fechada')
        continue

aliveTicks = 0

def connect_and_subscribe():
    global client_id, mqtt_server, topic_sub, server_port, mqtt_user, mqtt_password

    client = MQTTClient(client_id, mqtt_server, server_port, mqtt_user, mqtt_password)
    
    client.set_callback(sub_cb)
    client.connect()
    client.subscribe(topic_sub)

    print('Conectado ao %b MQTT Broker, recebendo os tópicos %t' % (mqtt_server, topic_sub))
    
    return client

def restart_and_reconnect():
    print('Failed to connect to MQTT Broker. Trying reconnection...')

    time.sleep(10)

    machine.reset()

def sub_cb(topic, msg):
    global topic_sub

    if (len(msg) == 3):
        if topic == topic_sub and msg == b'FRT':
            robot.moveFront()
        elif topic == topic_sub and msg == b'PAR':
            robot.stop()
        elif topic == topic_sub and msg == b'ESQ':
            robot.moveLeft()
        elif topic == topic_sub and msg == b'DIR':
            robot.moveRight()
        elif topic == topic_sub and msg == b'TRS':
            robot.moveReverse()

try:
    client = connect_and_subscribe()
except OSError as e:
    restart_and_reconnect()

while True:

    try:
        
        client.check_msg()

        if (time.time() - last_message) >= message_interval:

            distance = distSensor.distance_cm()

            last_message = time.time()

            aliveTicks += 1

    except OSError as e:
        restart_and_reconnect()

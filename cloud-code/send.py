import random
import time
import requests
import json

TOKEN = "BBFF-Avawe0nQFfP2VIIIcuzZAj7vw6fVXL"
DEVICE_LABEL="cpetech"
VARIABLE_LABEL_1 = "rouge"
VARIABLE_LABEL_2 = "vert"
VARIABLE_LABEL_3 = "bleu"
VARIABLE_LABEL_4 = "final_color"
VARIABLE_LABEL_5 = "distance"

def get_hex(val):
	hexadecimal = str(hex(val).lstrip("0x").upper())
	return hexadecimal

def build_payload(variable_1, variable_2, variable_3, variable_4, variable_5):

    value_1 = random.randint(0,255)
    value_2 = random.randint(0,255)
    value_3 = random.randint(0,255)
    value_4 = random.randint(0,16777215)
    value_5 = random.randint(0, 20)


    payload = {variable_1: {"value": value_1, "context": {"hexa": get_hex(value_1)}},
               variable_2: {"value": value_2, "context": {"hexa": get_hex(value_2)}},
               variable_3: {"value": value_3, "context": {"hexa": get_hex(value_3)}},
               variable_4: {"value": value_4, "context": {"hexa": get_hex(value_4)}},
               variable_5: value_5}

    return payload

def post_request(payload):
    # Creates the headers for the HTTP requests
    url = "http://things.ubidots.com"
    url = "{}/api/v1.6/devices/{}".format(url, DEVICE_LABEL)
    headers = {"X-Auth-Token": TOKEN, "Content-Type": "application/json"}

    # Makes the HTTP requests
    status = 400
    attempts = 0
    while status >= 400 and attempts <= 5:
        req = requests.post(url=url, headers=headers, data=json.dumps(payload))
        status = req.status_code
        attempts += 1
        time.sleep(1)

    # Processes results
    if status >= 400:
        print("[ERROR] Could not send data after 5 attempts, please check \
            your token credentials and internet connection")
        return False

    print("[INFO] request made properly, your device is updated")
    return True


def main():
    payload = build_payload(
        VARIABLE_LABEL_1, VARIABLE_LABEL_2, VARIABLE_LABEL_3, VARIABLE_LABEL_4, VARIABLE_LABEL_5)

    print("[INFO] Attemping to send data")
    post_request(payload)
    print("[INFO] finished")


if __name__ == '__main__':
    while (True):
        main()
        time.sleep(15)

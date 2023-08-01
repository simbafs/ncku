import os
import sys
import textwrap
import time

import requests
import telebot
from bs4 import BeautifulSoup
from dotenv import load_dotenv

load_dotenv()


def parseHeader(headerText):
    headers = {}

    # Split the input string into lines
    lines = headerText.strip().split("\n")

    for line in lines:
        # Split each line by the first colon to separate key and value
        key, value = line.split(":", 1)
        headers[key.strip()] = value.strip()

    return headers


def get_text_by_css_selector(url, selector, printStatus=False):
    try:
        # Send an HTTP GET request to the URL

        headers = parseHeader(
            """
User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:109.0) Gecko/20100101 Firefox/116.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8
Accept-Language: en-US,en;q=0.8,zh-TW;q=0.5,zh;q=0.3
Accept-Encoding: gzip, deflate, br
Referer: https://course.ncku.edu.tw/index.php?c=qry11215&m=en_query&i=BDNRbgYwV2QFfAstUT0APlVhVHNUZlMiWmkJaQI6DTZXbAd8UzkBagJqVj5VagoxCTYGPlVhBmoAeQUnAzpWYwBsASZQMVA8BXdQcVFYUjMOb1J1VT9Wdgg6CDtQaF93Vh1XZwMiCmBXewAsBnMONAxjVW0HIAAkAiICaFQ2U2sEYlFuBnhXIwV0C2RRNgA1VXlUNlQnUztaMAkyAjENPFcr
DNT: 1
Connection: keep-alive
Cookie: _ga=GA1.3.381219810.1673964398; _ga_V5263G30EE=GS1.1.1690852185.320.1.1690852558.0.0.0; _ga_9VR7HBB4SG=GS1.1.1687957937.7.0.1687957937.60.0.0; AMCV_4D6368F454EC41940A4C98A6%40AdobeOrg=-2121179033%7CMCIDTS%7C19523%7CMCMID%7C12671621494609851332063067034236606133%7CMCAID%7CNONE%7CMCOPTOUT-1686749625s%7CNONE%7CMCAAMLH-1687347225%7C11%7CMCAAMB-1687347225%7Cj8Odv6LonN4r3an7LhD3WZrU1bUpAkFkkiY1ncBR96t2PTI%7CMCSYNCSOP%7C411-19530%7CvVersion%7C5.3.0; s_pers=%20v8%3D1686742425397%7C1781350425397%3B%20v8_s%3DMore%2520than%252030%2520days%7C1686744225397%3B%20c19%3Dpr%253Apure%2520portal%253Apersons%253Aview%7C1686744225399%3B%20v68%3D1686742421172%7C1686744225400%3B; _ga_8RY35M6ZMQ=GS1.1.1690853311.10.0.1690853311.0.0.0; _ga_WHBRRJE1JV=GS1.1.1690298802.14.1.1690298834.0.0.0; _ga_YTL27NBKJ1=GS1.1.1686673400.7.1.1686673853.0.0.0; _ga_TKEHRTBPD6=GS1.1.1690760071.15.1.1690760097.0.0.0; _ga_BSPNZQ67NJ=GS1.1.1690760097.14.1.1690760238.0.0.0; _ga_8LGPXZ8D11=GS1.1.1687840960.4.0.1687840964.0.0.0; __dtsu=6D001683526930C7219E3255D732F50D; _ga_7TZLNDHBYS=GS1.1.1683905548.1.0.1683905556.0.0.0; _ga_H1MCL60QVP=GS1.1.1684898230.1.0.1684898236.0.0.0; _ga_FHTS9H202Z=GS1.1.1684918248.2.1.1684921479.0.0.0; _ga_H6F5F49WXK=GS1.1.1687957937.3.0.1687957937.60.0.0; cos_lang=cht; SSO=adc313fd46be8056305dc9a4aa926d71; PHPSESSID=C24106082c8f410e978b3e94b3c4a7c0f6285ff71; AMCVS_4D6368F454EC41940A4C98A6%40AdobeOrg=1; s_sess=%20s_cpc%3D0%3B%20s_sq%3D%3B%20s_ppvl%3Dpr%25253Apure%252520portal%25253Apersons%25253Asimilar%252C64%252C64%252C889%252C1920%252C889%252C1920%252C1080%252C1%252CP%3B%20s_ppv%3Dpr%25253Apure%252520portal%25253Apersons%25253Aview%252C77%252C40%252C3913%252C1920%252C889%252C1920%252C1080%252C1%252CP%3B%20e41%3D1%3B%20s_cc%3Dtrue%3B; COURSE_WEB=ffffffff8f7cbb1d45525d5f4f58455e445a4a423660; COURSE_CDN=ffffffff8f7ce72345525d5f4f58455e445a4a42cbd9; _gid=GA1.3.1739964840.1690853312
Upgrade-Insecure-Requests: 1
Sec-Fetch-Dest: document
Sec-Fetch-Mode: navigate
Sec-Fetch-Site: same-origin
TE: trailers
        """
        )
        print("Sending HTTP GET request...") if printStatus else None
        response = requests.get(
            url,
            headers=headers,
            timeout=10,
        )

        print("Response received!") if printStatus else None

        # Check if the request was successful (status code 200)
        if response.status_code == 200:
            print("BeautifulSoup parsing...") if printStatus else None
            # calculate parse time
            start_time = time.time()
            # Parse the HTML content using BeautifulSoup
            soup = BeautifulSoup(response.content, "lxml")
            print("BeautifulSoup parsed!") if printStatus else None
            print(
                "--- {:.2f} seconds ---".format(time.time() - start_time)
            ) if printStatus else None

            # Find all elements matching the CSS selector
            elements = soup.select(selector)

            if len(elements) == 0:
                print(
                    f"Error: No element found with the CSS selector '{selector}'"
                ) if printStatus else None
                print(soup) if printStatus else None
                return None

            # Extract and return the text content of the elements
            text_content = [element.text.strip() for element in elements]
            enrollment = text_content[0].split("/")
            return {
                "enrolled": enrollment[0],
                "available": enrollment[1],
            }

        else:
            print(
                f"Error: Failed to fetch data from {url}. Status code: {response.status_code}"
            )
            return None

    except requests.exceptions.RequestException as e:
        print(f"Error: {e}")
        return None


def startPolling(bot, delay=300):
    url = "https://course.ncku.edu.tw/index.php?c=qry11215&m=en_query&i=U2RUawA2BjULclF3VzsBP1ZiU3RebAd2CDsHZwU9CzBVblYtVjxWPVM7UzsDPA02WmVVbVJmB2sFfF99Bj8GNgpmUHcIegFjBCQLZQInAjcCPVNsUiFXNV91BjwHeFwrAHJRawAyC2AGdQYlVHANNg0yUGgANQJuUSgHK1MjAztTNFRrACcGaAsrUT9XYwE0VmlTbV5y"
    selector = "#A9-table > tbody:nth-child(2) > tr:nth-child(1) > td:nth-child(8)"
    targetChat = "901756183"
    printStatus = True

    initStatus = get_text_by_css_selector(url, selector, printStatus=printStatus)
    while True:
        time.sleep(delay)
        status = get_text_by_css_selector(url, selector, printStatus=printStatus)
        if status != initStatus:
            print("Change!")
            print(status)
            bot.send_message(
                targetChat,
                textwrap.dedent(
                    """
                    Change! {}
                    enrolled: {}
                    available: {} """.format(
                        telebot.formatting.hlink("link", url),
                        status["enrolled"],
                        status["available"],
                    )
                ),
                parse_mode="HTML",
            )
        else:
            print("not change")


token = os.getenv("BOTTOKEN")
if token is None:
    print("Error: No token provided")
    sys.exit(1)

bot = telebot.TeleBot(token)
startPolling(bot)

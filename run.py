from openai import OpenAI

client = OpenAI(
    base_url='https://api.openai-proxy.org/v1',
    api_key='sk-KMdHj9SwoI5LSCpuOfpfMDCAD0E026mGUv6CgGW0l2FH8Qji',
)

response = client.chat.completions.create(
    messages=[
        {
            "role": "user",
            "content": "Say hi",
        }
    ],
    model="gpt-3.5-turbo",
)

print(response.choices[0].message.content)
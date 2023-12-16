## Inworld.AI Account
To use the Inworld Sample Project, first create an account @ https://studio.inworld.ai

## Clone Workspace
Navigate to https://studio.inworld.ai/workspaces and click 'Import/Export'

Select 'Import Workspace' and use Token: 'QssFTLsjE2sQ'

WORKSPACES/GODOT should be found, press 'Confirm import'

Navigate to your new workspace, there will be 4 characters 'Carey', 'Russ', 'Vik', and 'Wilson'

## Project Configuration
The URL of your workspace in studio will be https://studio.inworld.ai/workspaces/{workspace-name}/

On the InworldSession Node, replace the 'Workspace name' field to your new workspace id

Under 'Developer tools' > 'Integrations', select '+ Generate new key' under the 'API Keys section'

Click 'Copy Base64' and paste the resulting token into the 'Auth' field of the Inworld Session Node

Note: The Auth token should be kept private, do not upload this publicly.

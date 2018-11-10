
platform :ios, '9.0'

target 'ScreamBoy' do
	# Comment the next line if you're not using Swift and don't want to use dynamic frameworks
	use_frameworks!

	# Pods for ScreamBoy
	pod 'Beethoven'

end

post_install do |installer|
    installer.pods_project.targets.each do |target|
        if target.name == 'Beethoven'
            target.build_configurations.each do |config|
                config.build_settings['SWIFT_VERSION'] = '4.0'
            end
        end
    end
end
